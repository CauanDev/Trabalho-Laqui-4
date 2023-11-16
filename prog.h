#define QTDE_ELEMENTOS_LIDOS 1
#define TAMANHO 1000
struct NO 
{
    int valor;
    int tamanho;
    int quntdFilho;
    int tamanhoNO;
    struct NO *filho;
    struct NO *irmao;
    struct NO *pai;
};

typedef struct 
{
    struct NO *raiz;
    int *vetor;
    int indice;
    int *pilha;
    int indice1;
} ARVORE;



int Leitura(int v[]);
void construirArvore(ARVORE *arvore);
struct NO *criarNo(int valor);
struct NO *buscarNo(struct NO *raiz, int valorProcurado);
int Cont(int numero) ;
int AdicionarIrmao(struct NO *irmao,int vetor[],int inicio, int fim);
int TamanhoTotal(struct NO* no,int op);
int ImprimeIrmao(struct NO *raiz,int tamanho, int vetor[]);
int CalculoTamanho(struct NO *raiz,int op);
void GerenciaImpressao(struct NO *raiz,int *pilha,int tamanho);
int verificarParentesco(int valor1, int valor2, struct NO *raiz);
int AdministraPilha(int valor2,struct NO *raiz, int *pilha,int *indice);
int Gerente(int *pilha, int indice, struct NO *raiz);
int TemNaPilha(int tamanho,int valor, int vetor[]);
void ImprimeFilho(struct NO *raiz);

