#include "FCMatrixAlgorithm.h"

//#define DEBUGBUILD3

int FCMatrixAlgorithm::GaussElimination(FCMatrix &matrix)
{
#ifdef DEBUGBUILD3
    printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
    int sign = 1;
    int counter = 0;
    for (int i = 0; i < matrix.GetRowN() - 1; i++)
    {
        while (matrix[i][i] == 0)
        {
            counter++;
            if (counter == matrix.GetRowN())
            {
                counter = 0;
                i++;
                break;
            }
            matrix.SwapLines(i, i + counter);
            sign *= -1;
        }
        for (int j = i + 1; j < matrix.GetRowN(); j++)
        {
            double factor = matrix[j][i] / matrix[i][i];
            matrix[j] -= matrix[i] * (factor);
        }
    }
    return sign;
}

//LU Decomposition method (Doolittle)
FCMatrixFull *FCMatrixAlgorithm::LUDecomposition_Doolittle(FCMatrix &matrix)
{

    Vec v(matrix.GetColN(), 0);
    std::vector<Vec> vv;

    if (matrix.Determinant() != 0) //Verificação se a matriz é quadrada, só se vão resolver sistemas possíveis e determinados
    {

        for (int i = 0; i < matrix.GetRowN(); i++)
        {
            vv.push_back(v);
        }
        FCMatrixFull low(vv); //Inicialização dos objetos onde vão ser guardadas as matrizes 'L' e 'U'
        FCMatrixFull up(vv);
        int n = matrix.GetColN();

        //Decomposição da matriz em matrizes triangular superior e triangular inferior
        for (int i = 0; i < n; i++)
        {
            // Triangular Superior
            for (int k = i; k < n; k++)
            {
                //Acumulação dos produtos entre low[i][j](Futura matriz triangular inferior) * up[j][k](Futura  matriz triangular superior)
                double sum = 0;
                for (int j = 0; j < i; j++)
                    sum = sum + (low[i][j] * up[j][k]);

                //Atribuição do valor atualizado aos elementos da matriz triagular superior dados por up[i][k]
                up[i][k] = matrix[i][k] - sum;
            }

            // Triangular Inferior
            for (int k = i; k < n; k++)
            {
                if (i == k)
                    low[i][i] = 1; // Diagonal a 1
                else
                {
                    //Acumulação dos produtos entre low[k][j](Futura matriz triangular superior) * up[j][i]  (Futura matriz triangular inferior)
                    double sum = 0;
                    for (int j = 0; j < i; j++)
                        sum = sum + (low[k][j] * up[j][i]);
                    //Atribuição do valor atualizado aos elementos da matriz triagular inferior dados por low[k][i]
                    low[k][i] = (matrix[k][i] - sum) / up[i][i]; //Divisão pelo coeficiente da diagonal para  garantir que a diagonal da matriz trinagular inferior...
                }                                                //é constituída apenas por 1's
            }
            /*std::cout << low << std::endl;
            std::cout << up << std::endl;*/
            //Uncomment for testing...
        }
        FCMatrixFull *LU = new FCMatrixFull[2]; //Armazenamento das matrizes triangulares inferior e superior...
        LU[0] = low;                            //que resultaram da aplicação do processo de simplificação de Doolittle num ponteiro para objetos do tipo FCMatrixFull
        LU[1] = up;

        return LU;
    }
    else
    {
        //Mensagem de erro dada em caso de não ser possível resolver o sistema
        std::cout << std::endl
                  << "Não é possível resolver o sistema. Irá ser retornado um ponteiro para FCMatrixFull default...!" << std::endl;
        FCMatrixFull *LU = new FCMatrixFull[2];
        return LU;
    }
}