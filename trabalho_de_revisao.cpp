#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

struct Aluno {int codigoA; string nomeA; int CPF; };

struct Disciplina {int codigoD; string nomeD; string professor; int credito; };

struct Matricula {int codigo_aluno; int codigo_disciplina; string periodo; };

void inicializacao();
void arquivo_de_dados();
void inserir_aluno();
void inserir_disciplina();
void realizar_matricula();
void remover_disciplina();
void carregarDados();
void disciplinas_do_aluno();
void remover_aluno();
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
            cout<<"\n Voce escolheu encerrar o programa!";
            return 0;
    }
    goto inicio;

}


void arquivo_de_dados(){
    ofstream arquivo("Dados.txt");
    arquivo << "Alunos Cadastrados: \n";
    for(const auto& aluno : alunos){
        arquivo << aluno.codigoA << ' ' << aluno.nomeA<<' '<< aluno.CPF;}

    arquivo<< "Disciplinas Cadastradas: \n";
    for(const auto& disciplina : disciplinas){
        arquivo << disciplina.codigoD << ' '<< disciplina.nomeD << ' '<< disciplina.professor<< ' '<< disciplina.credito;}

    arquivo<< "Matriculas feitas:\n";
    for(const auto& matricula : matriculas){
        arquivo<< matricula.codigo_aluno << ' '<< matricula.codigo_disciplina << ' '<< matricula.periodo;
}
arquivo.close();
}

void carregarDados() {
    ifstream arquivo("Dados.txt");
    if (!arquivo.is_open()) {
        return;
    }

    string linha;
    while (getline(arquivo, linha)) {
        if (linha == "Alunos Cadastrados: \n") {
            while (getline(arquivo, linha) && linha != "Disciplinas Cadastradas: \n") {
                Aluno aluno;
                stringstream ss(linha);
                ss >> aluno.codigoA >> aluno.nomeA >> aluno.CPF;
                alunos.push_back(aluno);
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
    cout<<"2. Remover Aluno" << endl;
    cout<<"3. Inserir Disciplina "<< endl;
    cout<<"4. Remover Disciplina"<< endl;
    cout<<"5. Realizar matrícula"<< endl;
    cout<<"6. Alunos nessa disciplina"<< endl;
    cout<<"7. Disciplinas desse Aluno"<< endl;
    cout<<"8. Fechar Programa.\n";
}

void inserir_aluno(){
    Aluno aluno;
    cout<< "Escreva o codigo do aluno:\n";
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
    cout<<"Escreva o codigo da disciplina:\n";
    cin>> disciplina.codigoD;
    cout<<"\nEscreva o nome da disciplina:\n";
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
    for(auto i= alunos.begin(); i!=alunos.end(); i++){
        if(i->codigoA == codigo)//i está toamndo o valor de cada elemento do vetor que por si é uma struct
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
    for(auto i= disciplinas.begin(); i!=disciplinas.end(); i++){
        if(i->codigoD == codigo)//i está toamndo o valor de cada elemento do vetor que por si é uma struct
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
    for(auto i= matriculas.begin(); i!=matriculas.end(); i++){
        if(i->codigo_aluno  == codigo){
            cout<<"\n Essas sao as disciplinas que esse aluno esta cursando:\n";
            for(auto j=disciplinas.begin(); j!=disciplinas.end();j++){
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
    for(auto i= matriculas.begin(); i!=matriculas.end(); i++){
        if(i->codigo_disciplina==codigo){
            disciplinaencontrada = true;
            
            for(auto j=alunos.begin(); j!=alunos.end();j++){
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