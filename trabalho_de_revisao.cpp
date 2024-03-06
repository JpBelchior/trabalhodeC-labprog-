#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

struct Aluno {int codigoA; string nomeA; int CPF; };

struct Disciplina {int codigoD; string nomeD; string professor; int credito; };

struct Matricula {int codigo_aluno; int codigo_disciplina; string periodo; };

void inicializacao(); // menu de opçoes
void arquivo_de_dados(); //inserindo os dados de cada vector no arquivo
void inserir_aluno(); // adicionando alunos no vector alunos
void inserir_disciplina();// adicionando diciplina no vector disciplinas
void realizar_matricula();// adicionando a matricula no vector matriculas
void remover_disciplina();// removendo disciplina do vector disciplina
void carregarDados(); // lendo os dados escritos no arquivo de texto
void disciplinas_do_aluno();
void remover_aluno();// removendo aluno do vector alunos
void alunos_da_disciplina();


vector <Aluno> alunos;
vector <Disciplina> disciplinas;
vector <Matricula> matriculas;


int main(){
    int opcao=0;
    inicio:
    inicializacao();
    cout<< " Bom dia!\n"<< " Digite o numero da sua opcao:\n ";
    cin >> opcao;
    switch(opcao){
        case 1:
            cout<<"\n Voce escolheu a opcao de insercao de aluno:\n Para isso, siga os comandos a seguir.\n";
            inserir_aluno();
            break;
        
        case 2:
            cout<<"\n Voce escolheu a opcao de remocao de aluno:\n Para isso, siga os comandos a seguir.\n";
            remover_aluno();
            break;
        
        case 3:
            cout<<"\n Voce escolheu a opcao de insercao de disciplina:\n Para isso, siga os comandos a seguir.\n";
            inserir_disciplina();

            break;

        case 4:
            cout<<"\n Voce escolheu a opcao de remocao de disciplina:\n Para isso, siga os comandos a seguir.\n";
            remover_disciplina();

            break;

        case 5:
            cout<<"\n Voce escolheu a opcao de matricular um aluno em alguma disciplina:\n Para isso, siga os comandos a seguir.\n";
            realizar_matricula();
            break;
        case 6:
            cout<<"\n Voce escolheu a opcao de ver quais alunos estao matriculados nessa disciplina\n";
            alunos_da_disciplina();
            break;

        case 7:
            cout<<"\n Voce escolheu a opcao de ver quais disciplinas esse aluno cursa \n";
            disciplinas_do_aluno();
            break;
        
        case 8:
            cout<< "\n Salvamos os dados inseridos!\n";
            arquivo_de_dados();
            break;
        case 9:
            cout<< "\n Carregamos os dados!\n";
            carregarDados();
            break;

        case 10:
            cout<<"\n Voce escolheu encerrar o programa!";
            return 0;
    }
    goto inicio;

}


void arquivo_de_dados(){
    ofstream arquivo("Dados.txt");//abertura de arquivo para escrita
    arquivo << "Alunos Cadastrados: \n";
    for(const Aluno& aluno : alunos)/*definimos a variavel aluno que representara cada elemento do vector aluno, auto defini automaticamente
    o tipo de variavel e o const é pra nao altera-la durante o loop*/
    {
        arquivo << aluno.codigoA << ' ' << aluno.nomeA<<' '<< aluno.CPF <<"\n";}

    arquivo<< "Disciplinas Cadastradas: \n";
    for(const Disciplina& disciplina : disciplinas){
        arquivo << disciplina.codigoD << ' '<< disciplina.nomeD << ' '<< disciplina.professor<< ' '<< disciplina.credito<< "\n";}

    arquivo<< "Matriculas feitas:\n";
    for(const Matricula& matricula : matriculas){
        arquivo<< matricula.codigo_aluno << ' '<< matricula.codigo_disciplina << ' '<< matricula.periodo << "\n";
}
arquivo.close();
}

void carregarDados() {
    ifstream arquivo("Dados.txt");//abertura de arquivo para leitura
    if (!arquivo.is_open()) {
        return;
    }

    string linha;
    while (getline(arquivo, linha))//lendo o arquivo armazenando uma string
     {
        if (linha == "Alunos Cadastrados: \n") {
            while (getline(arquivo, linha) && linha != "Disciplinas Cadastradas: \n") {
                Aluno aluno;
                stringstream ss(linha); //divide a string nos espaços conseguindo separar codigo nome e cpf.
                ss >> aluno.codigoA >> aluno.nomeA >> aluno.CPF;
                alunos.push_back(aluno); // adicionando parte do arquivo no vector
            }
        } else if (linha == "Disciplinas Cadastradas: \n") {
            while (getline(arquivo, linha) && linha != "Matriculas feitas:\n") {
                Disciplina disciplina;
                stringstream ss(linha);
                ss >> disciplina.codigoD >> disciplina.nomeD >> disciplina.professor >> disciplina.credito;
                disciplinas.push_back(disciplina);
            }
        } else if (linha == "Matriculas feitas:\n") {
            while (getline(arquivo, linha)) {
                Matricula matricula;
                stringstream ss(linha);
                ss >> matricula.codigo_aluno >> matricula.codigo_disciplina >> matricula.periodo;
                matriculas.push_back(matricula);
            }
        }
    }

    arquivo.close();
}

void inicializacao(){
    cout<< " =====MENU=====\n";
    cout<<"1. Inserir Aluno."<< endl;
    cout<<"2. Remover Aluno." << endl;
    cout<<"3. Inserir Disciplina. "<< endl;
    cout<<"4. Remover Disciplina."<< endl;
    cout<<"5. Realizar matrícula."<< endl;
    cout<<"6. Alunos nessa disciplina."<< endl;
    cout<<"7. Disciplinas desse Aluno."<< endl;
    cout<<"8. Salvamentos de dados.\n";
    cout<<"9. Carregamento de dados.\n";
    cout<<"10. Fechar o programa.\n";
}

void inserir_aluno(){
    Aluno aluno;
    cout<< " Escreva o codigo do aluno:\n RESTRICAO: Primeiro numero diferente de 0 \n";
    cin>> aluno.codigoA;
    cout<<"\n Escreva o nome do aluno:\n";
    cin.ignore();
    getline(cin,aluno.nomeA);
    cout<< "\n Escreva o CPF do aluno:\n";
    cin.ignore();
    cin>>aluno.CPF;
    alunos.push_back(aluno);
}

void inserir_disciplina(){
    Disciplina disciplina;
    cout<<" Escreva o codigo da disciplina:\n";
    cin>> disciplina.codigoD;
    cout<<"\n Escreva o nome da disciplina:\n (Se tiver um numero digite em algarismos romanos)\n";
    cin.ignore();
    getline(cin,disciplina.nomeD);
    cout<<"\n Escreva o nome do professor da disciplina:\n";
    getline(cin, disciplina.professor);
    cout<<"\n Escreva o numero de creditos da disciplina\n";
    cin>> disciplina.credito;
    disciplinas.push_back(disciplina);
}

void realizar_matricula(){
    Matricula matricula;
    cout<<"\n Escreva o codigo do aluno que realizara a matricula:\n";
    cin>> matricula.codigo_aluno;
    cout<<"\n Escreva o codigo da disciplina de matricula:\n";
    cin.ignore();
    cin >> matricula.codigo_disciplina;
    cout<<"\n Escreva o periodo de matricula da forma: ano semestre\n EX:2018.2 \n";
    cin.ignore();
    getline(cin, matricula.periodo);
    matriculas.push_back(matricula);
}

void remover_aluno(){
    int codigo=0;
    cout<<"\n Digite o codigo do aluno que sera removido:\n";
    cin>> codigo;
    for(auto i= alunos.begin(); i!=alunos.end(); i++)//criando ima variavel i do tipo do elemento de alunos e vasculhando o vector do inicio ao fim
        {
        if(i->codigoA == codigo)//i está toamndo o valor de cada elemento do vetor e apontando pra o odigo daquela struct
        {
            alunos.erase(i);
            cout<<"Aluno de codigo " <<codigo << " removido\n";
        }
        else{
            cout<<"\n Aluno nao encontrado\n";
        }
    }
}

void remover_disciplina(){
    int codigo=0;
    cout<<"\n Digite o codigo da disciplina que será removida:\n";
    cin>> codigo;
    vector<Disciplina>::iterator i;
    for( i= disciplinas.begin(); i!=disciplinas.end(); i++){
        if(i->codigoD == codigo)
        {
            disciplinas.erase(i);
            cout<<"Disciplina de codigo" <<codigo << " removida\n";
        }
        else{
            cout<<"\n Disciplina nao encontrado\n";
        }
    }
}

void disciplinas_do_aluno(){
    int z=0, codigo;
    bool alunoencontrado=false;
    cout<<"\n Digite o codigo do aluno:\n";
    cin>> codigo;
    vector<Matricula>::iterator i;
    for( i= matriculas.begin(); i!=matriculas.end(); i++){
        if(i->codigo_aluno  == codigo){
            cout<<"\n Essas sao as disciplinas que esse aluno esta cursando:\n";
            vector<Disciplina>::iterator j;
            for(j=disciplinas.begin(); j!=disciplinas.end();j++){
                if(j->codigoD== i-> codigo_disciplina){
                    z+=1;
                    cout<< z << '.' << j-> nomeD<< "\n";
                }
            }
        }
    }
    if(!alunoencontrado){
        cout << "\nNão há disciplina cadastrada com esse código!\n";   
    }
}

void alunos_da_disciplina(){
    int z=0, codigo;
    bool disciplinaencontrada=false;
    cout<<"\n Digite o codigo da disciplina:\n";
    cin>> codigo;
    cout<<"\n Esses sao os alunos que estao matriculados nessa disciplina:\n";
    vector<Matricula>::iterator i;
    for(i= matriculas.begin(); i!=matriculas.end(); i++){
        if(i->codigo_disciplina==codigo){
            disciplinaencontrada = true;
            vector<Aluno>::iterator j;
            for( j=alunos.begin(); j!=alunos.end();j++){
                if(j->codigoA == i->codigo_aluno){
                    z+=1;
                    cout<< z << '.' << j->nomeA<< "\n";
                }
            }
        }
    }
    if(!disciplinaencontrada){
        cout << "\nNão há disciplina cadastrada com esse código!\n";
    }
}
