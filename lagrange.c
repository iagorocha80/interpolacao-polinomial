#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
float* ler_x(){
    FILE *fp;
    float coeff;
    int grau, i;
    fp = fopen("X.txt", "r");
    if (fp == NULL){
        printf("Erro ao abrir o ficheiro!\n");
    }
    fscanf(fp, "%d", &grau);
    float* x;  //Definicao do array dinamico para os coeficientes de X
    x=calloc(grau, sizeof(float)); //Configuracao do array dinamico

    for(i=0; i<grau; i++){
        fscanf(fp, "%f", &coeff);
        *(x+i) = coeff;
    }
    fclose(fp);
    return x;
}

float* ler_y(){
    FILE *fp;
    float coeff;
    int grau, i;
    fp = fopen("Y.txt", "r");
    if (fp == NULL){
        printf("Erro ao abrir o ficheiro!\n");
    }
    fscanf(fp, "%d", &grau);
    float* y;  //Definicao do array dinamico para os coeficientes de Y
    y=calloc(grau, sizeof(float)); //Configuracao do array dinamico

    for(i=0; i<grau; i++){
        fscanf(fp, "%f", &coeff);
        *(y+i) = coeff;
    }
    fclose(fp);
    return y;
}

int ler_n(){
    FILE *fp;
    float coeff;
    int grau, i;
    fp = fopen("Y.txt", "r");
    if (fp == NULL){
        printf("Erro ao abrir o ficheiro!\n");
        return -1;
    }
    fscanf(fp, "%d", &grau);
    fclose(fp);
    return grau;
}


void Lagrange(float x[],float y[], float xp, int n){ // Calculo do valor de um polinomio por meio da interpolacao de Lagrange
    system ("clear");
    int i, j;
    double L, P;
    P = 0;
    for (i=0;i<n;i++){
        L=1;
        for (j=0;j<n;j++){
            if(i != j){
                L = L * (xp-x[j])/(x[i]-x[j]);
            }
        }
        printf("L%d(%.3f)=%.3f\n",i,xp,L);
        P = P + y[i]*L;
    }
    printf("\n\n\n\n\n\n Prima enter para Continuar: \n");
    getchar();
    printf("O valor do polinomio em x=%.3f eh %.3f \n",xp, P);
    printf("\n\n\n\n\n\n Prima enter para Continuar: \n");
    getchar();      
}



double DD(float* x,float* y, int n,int g){ //Tabela de Diferencas Dividas usada na interpolacao
    system ("clear");
    double DD[n][n];
    double fg;
    int i,j,c=0,l,k;
    for (i=0; i<n; i++){
        DD[i][0]=y[i];
    }
    for (j=1; j<g; j++){
        for (i=j; i<g; i++){
            DD[i][j] = (DD[i][j-1] - DD[i-1][j-1])/(x[i]-x[i-j]);
            fg=DD[i][j];
            printf("M[%d,%d]=%.3f \t fg=%f\n",i,j,DD[i][j], fg);
        }
        printf("\n\n\n\n\n\n Prima enter para Continuar: \n");
    	getchar();
    }
    
    return fg;
}

void erro_interpolacao(float X[],float xp, int nos, double fg){ //Calculo do Erro
    system ("clear");
    int i=0;
    double erro,aux=1;
    for(i=0;i<nos;i++){
    	aux*=fabs((xp-X[i]));
    }
    //erro= erro*fg ;
    erro=fabs(aux*fg);
    printf("\n\n\n\n\n\n Prima enter para Continuar: \n");
    getchar();
    printf("O erro da aproximacao para o ponto %f eh %f",xp, erro);
    printf("\n\n\n\n\n\n Prima enter para Continuar: \n");
    getchar();
}

int menuinterpolacao(){
    float* x= ler_x(); //Definicao do X da interpolacao
    float* y= ler_y(); //Definicao do Y da interpolacao
    system ("clear");
    char op;
    float xp;
    double fg;
    int nos,g=4, n, i=0,l=0;
    n=ler_n();
    printf("Prima, seguido por enter para confirmar, a quantidade de nodos desejados para o calculo\n");
    scanf("%d", &nos);
    printf("Prima, seguido por enter para confirmar, o valor do ponto desejado para o calculo\n");
    scanf("%f", &xp);
    printf("Prima, seguido por enter para confirmar, ate qual grau deseja que as Diferenças Definidas sejam calculadas\n");
    scanf("%d", &g);
    system ("clear");
    float X[nos];
    float Y[nos];
    printf("X= ");
    for(i=0;i<n;i++){
        printf(" %f \t",x[i]);
    }
    printf("\n");
    printf("Y= ");
    for(i=0;i<n;i++){
        printf(" %f \t",y[i]);
    }
    printf("\n");
    printf("Selecione dentre os valores de X acima o valor dos nodos \n");
    for(i=0;i<nos;i++){
        scanf("%f", &X[i]);
    }
    for(i=0;i<nos;i++){
        for(l=0;l<n;l++){
            if(x[l]==X[i]){
                Y[i]=y[l];
            }
        }
    }
    system ("clear");
    fg=DD(x, y, n, g);
    while(op!='s'){
        system ("cls");
        system ("cls");
        printf("\t\t\t Menu Interpolacao Polinomial pelo metodo de Lagrange\n");
        printf("1 - Tabela das Diferencas Divididas\n");
        printf("2 - Metodo de La Grange\n");
        printf("3 - Calculo do Erro de interpolacao\n");
        printf("0 - Instrucoes de Uso\n");
        printf("\n\n\n s - Encerrar programa \n\n");
       scanf("%c", &op);
        switch(op){
            case '1': DD(x, y, n, g); break;
            case '2': Lagrange(X, Y, xp, nos); break;
            case '3': erro_interpolacao(X, xp, nos, fg); break;
            case '0': printf("\n\n\n Para Interpolar um polinomo eh preciso por os valores de X e Y, precedidos por um numero inteiro que inca a quantidade de valores, da funcao respectivamente nos ficheiros X.txt e Y.txt, apos isso eh preciso entrar com os parametros(quantidade nos,ponto de interpolacao,quantidade de vezes que a DD eh executada e os valores de X a serem interpolados. Exatamente nesta ordem) via input.Prima enter para retornar ao menu\n\n\n");getchar(); break;
            case 'S': return(0);
        }

    };


}


int main() {
    menuinterpolacao();
    return 0;
}
