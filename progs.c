#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include "prog.h"


struct NO *criarNo(int valor) 
{
    struct NO *novoNo;
    novoNo = (struct NO *)malloc(sizeof(struct NO));
    novoNo->valor = valor;
    novoNo->quntdFilho = 0;
    novoNo->tamanhoNO = 0;
    novoNo->tamanho = Cont(valor);
    novoNo->filho = NULL;
    novoNo->irmao = NULL;
    novoNo->pai = NULL;
    return novoNo;    
}


void construirArvore(ARVORE *arvore) 
{   
    struct NO *novoNo;
    int inicio,fim,i=0;
    if (arvore->vetor[arvore->indice] == -1) 
    {
        
        for(i=0;i<=TamanhoTotal(arvore->raiz,0)/2;i++)
        {   
            putchar(32);       
        }
        printf("|%d|\n",arvore->raiz->valor); 
        for(i=0;i<=TamanhoTotal(arvore->raiz,0);i++)
        {   
            if(i == (TamanhoTotal(arvore->raiz,0)/2)+(arvore->raiz->tamanho/2))
            {
                putchar(124);  
            }
            else
            {
                putchar(95); 
            }
        }
        printf("\n");
        if(arvore->raiz->filho !=NULL)
        {
            if(arvore->indice1 > 0)
            {
                arvore->indice1 = Gerente(arvore->pilha,arvore->indice1,arvore->raiz); 
            }
            GerenciaImpressao(arvore->raiz->filho,arvore->pilha,arvore->indice1);
        }

    }
    if (arvore->vetor[arvore->indice] == 0) 
    {
        arvore->indice+=2;        
        arvore->raiz = criarNo(arvore->vetor[arvore->indice]);
        arvore->indice++;
        arvore->raiz->quntdFilho = arvore->vetor[arvore->indice];
        arvore->indice++;
        arvore->raiz->filho = criarNo(arvore->vetor[arvore->indice]);
        arvore->indice++;
        if(arvore->raiz->quntdFilho > 1)
        {
            inicio = arvore->indice;
            fim = ((arvore->indice)-1)+(arvore->raiz->quntdFilho);
            arvore->raiz->tamanhoNO = AdicionarIrmao(arvore->raiz->filho,arvore->vetor,inicio,fim);      
            arvore->indice += (arvore->raiz->quntdFilho)-1;  
        }


        construirArvore(arvore);      
    } 
    else 
    {  
        novoNo = buscarNo(arvore->raiz,arvore->vetor[arvore->indice]);
        arvore->pilha[arvore->indice1] = novoNo->valor;
        arvore->indice1++;
        arvore->indice++;        
        novoNo->quntdFilho = arvore->vetor[arvore->indice];
        arvore->indice++;
        novoNo->filho = criarNo(arvore->vetor[arvore->indice++]);;
        if(novoNo->quntdFilho>1)
        {
            inicio = arvore->indice;
            fim = ((arvore->indice)-1)+(novoNo->quntdFilho);            
            novoNo->tamanhoNO= AdicionarIrmao(novoNo->filho,arvore->vetor,inicio,fim);     
            arvore->indice += (novoNo->quntdFilho)-2;   
        }
        else
        {
            construirArvore(arvore); 
        }
        arvore->indice++;
        construirArvore(arvore);    
    }    
}
int verificarParentesco(int valor1, int valor2, struct NO *raiz)
{
    int veredito;
    struct NO *no1,*no2,*ex;
    no1 = buscarNo(raiz,valor1);
    no2 = buscarNo(raiz,valor2);  
    veredito = 0;

    
    if(no1->irmao != NULL)
    {
        if(no1->irmao->valor == valor2)
        {
            return 1;
        }
        ex = no1->irmao;
        while(ex->irmao != NULL)
        {
            if(ex->valor == valor2)
            {
                veredito = 1;
            }
            else
            {
                
                if(ex->irmao != NULL)
                {
                    ex = ex->irmao;                    
                }                
            }
        }        
    }
    if(veredito == 1)
    {
        return veredito;
    }
    if(no2->irmao != NULL)
    {
        if(no2->irmao->valor == valor1)
        {
            return 1;
        }
        ex = no2->irmao;
        while(ex->irmao != NULL)
        {
            if(ex->valor == valor1)
            {
                veredito = 1;
            }
            else
            {
                if(ex->irmao != NULL)
                {
                    ex = ex->irmao;
                }
            }
        }        
    }    


    return veredito;
}

int Gerente(int *pilha, int indice, struct NO *raiz)
{
    int i,j,cont = 0,inicio,fim;
    size_t tamanho = sizeof(pilha) / sizeof(pilha[0]);
    int *novapilha = (int *)malloc((tamanho) * sizeof(int));


    for(i=0;i <indice;i++)
    {
        inicio = 0;
        fim = 0;
        for(j = 1;j<indice;j++)
        {
            if(pilha[j] != -1 && pilha[i] != -1 && pilha[j] != 0 && pilha[i] != 0 && pilha[i] != pilha[j])
            {
                if(verificarParentesco(pilha[i],pilha[j],raiz))
                {
                    novapilha[cont] = pilha[i];
                    cont++;                    
                    novapilha[cont] = pilha[j];
                    pilha[j] = -1;
                    cont++;
                    novapilha[cont] = 0;
                    cont++;
                    fim = 1;
                }
            }
        }
        if(inicio == fim)
        {
               
            if(pilha[i] != -1)
            { 
                novapilha[cont] = pilha[i];
                cont++;  
                novapilha[cont] = 0;
                cont++;                    
            }           

        }
    }
    
    for(i = cont; novapilha[i]>0;i--); 
    j = 0;
    while(j!=i)
    {        
        pilha[j] = novapilha[j];
        j++;
    }
    return cont-1;
}
int TemNaPilha(int tamanho,int valor, int vetor[])
{
    int resultado = 0,i;
    for(i=0;i<=tamanho;i++)
    {
        if(vetor[i] == valor)
        {
            resultado = 1;
            break;
        }
    }
    return resultado;
}
void GerenciaImpressao(struct NO *raiz,int pilha[],int tamanho)
{
    int i = 0;
    struct NO *no,*principal;
    principal = raiz;

        if(principal->irmao != NULL)
        {
            
            if(ImprimeIrmao(principal,tamanho,pilha))
            {
                printf("\n");
                while(i!=tamanho)
                {
                    if(pilha[i] == 0)
                    {
                        printf("\n");
                    }
                    else
                    {
                        no = buscarNo(raiz,pilha[i]);
                        ImprimeFilho(no);                        
                    }
                    i++;
                }          

            }
        }        


}

int ImprimeIrmao(struct NO *raiz,int tamanho, int vetor[])
{    
    int i,tamanho1;
    tamanho1 = CalculoTamanho(raiz,1);
    for(i=0;i<=tamanho1;i++)
    {   
        if(i==abs(tamanho1/2))
        {
            printf("|%d|",raiz->valor);
            i+=3;
        }
        putchar(32);  
    }
    i = 0;
    if(raiz->irmao != NULL)
    {
       i = ImprimeIrmao(raiz->irmao,tamanho,vetor);
    }
    return TemNaPilha(tamanho,raiz->valor,vetor) + i;
}

int CalculoTamanho(struct NO *raiz,int op)
{   
    int tamanhoAtual;
    tamanhoAtual = raiz->tamanho;
    if (raiz == NULL) 
    {
        return 0;
    }
    /* So vai considerar os filhos a principio*/
    if(op)
    {
        if(raiz->filho!=NULL)
        {   
            tamanhoAtual += TamanhoTotal(raiz->filho,0);
        }
    }
    else
    {
        if(raiz->filho!=NULL)
        {   
            tamanhoAtual += TamanhoTotal(raiz->filho,0);
        }
        if(raiz->irmao!=NULL)
        {
            tamanhoAtual += TamanhoTotal(raiz->irmao,0);
        }
    }
    if(tamanhoAtual == raiz->tamanho)
    {
        tamanhoAtual = 2;
    }
    return tamanhoAtual;
}

int TamanhoTotal(struct NO *raiz,int op) 
{
    int tamanhoAtual;
    if (raiz == NULL) 
    {
        return 0;
    }
    tamanhoAtual = raiz->tamanho;
    if(op)
    {
        if(raiz->filho!=NULL)
        {
            tamanhoAtual += TamanhoTotal(raiz->filho,0);
        }
    }
    else
    {
        if(raiz->quntdFilho > 1)
        {   
            tamanhoAtual += TamanhoTotal(raiz->filho,0);
        }
        else
        {
            tamanhoAtual += TamanhoTotal(raiz->irmao,0);
        }   

    }
    return tamanhoAtual;
}

int Cont(int numero) 
{
    int quantidade = 0;
    while (numero != 0) 
    {
        numero /= 10;
        quantidade++;
    }
    quantidade+=2;
    if(quantidade %2 != 0)
    {
        quantidade++;
    }
    return quantidade;
}

int Leitura(int v[])
{
    int i = 0;
    while (fscanf(stdin, "%d", &v[i]) == QTDE_ELEMENTOS_LIDOS)
	{
        i++;
    }
    return i;           
}

struct NO *buscarNo(struct NO *raiz, int valorProcurado)
{
   
    struct NO *resultado = NULL; 
    if(raiz->valor == valorProcurado) 
    {  
        return raiz; 
    }
    if(raiz->irmao!=NULL)
    {
        if(raiz->irmao->valor==valorProcurado)
        {
            return raiz->irmao;
        }
        else
        {
            resultado = buscarNo(raiz->irmao, valorProcurado);   
        }
        
    }
    if(resultado != NULL)
    {
        return resultado;
    }
    if(raiz->filho != NULL)
    {   
        if(raiz->filho->valor == valorProcurado)
        {
            return raiz->filho;
        }
        else
        {
            resultado = buscarNo(raiz->filho, valorProcurado);     
        }        
    }
    if(raiz->irmao == NULL && raiz->filho == NULL)
    {
        return NULL;
    }
    if (resultado != NULL) 
    {
        return resultado; 
    }
    if(raiz == NULL)
    {
        return NULL;
    }
    return NULL; 
}

int AdicionarIrmao(struct NO *irmao,int vetor[],int inicio, int fim)
{
    struct NO *novo;
    int back = 0;
    if(inicio == fim)
    {
        return back +irmao->tamanho;        
    }
    else
    {
        novo = criarNo(vetor[inicio]);
        irmao->irmao = novo;
        back = irmao->tamanho + AdicionarIrmao(irmao->irmao,vetor,inicio+1,fim);
        return back;
    }
    
}

void ImprimeFilho(struct NO *raiz)
{
    int i,tamanho,j=0;
    struct NO *no;
    no = raiz->filho;
    tamanho = CalculoTamanho(raiz,1);
    while(j!=raiz->quntdFilho)
    {
        for(i=0;i<=tamanho;i++)
        {   
            if(i==abs(tamanho/2))
            {
                printf("|%d|",no->valor);
                i+=3;
            }
            putchar(32);  
        }  
        no = no->irmao;    
        j++;  
    }    
}