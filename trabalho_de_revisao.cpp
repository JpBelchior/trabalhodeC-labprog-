#include <bits/stdc++.h>
#include <iostream>
#include <string>

using namespace std;

struct Aluno {int codigoA; string nomeA; string CPF; };

struct Disciplina {int codigoD; string nomeD; string professor; int credito; };

struct Matricula {int codigo_aluno; int codigo_disciplina; string periodo; };

//Lista das funções utilizadas no codigo.

void arquivo_de_dados(); //inserindo os dados de cada vector no arquivo
void carregamentodados();//carrega tudo que esta no arquivo antes da execuçao do programa
void inicializacao(); // menu de opçoes
void inserir_aluno(); // adicionando alunos no vec₢tor alunos
void inserir_disciplina();// adicionando diciplina no vector disciplinas
void realizar_matricula();// adicionando a matricula no vector matriculas
void remover_matricula();//removendo matricula 
void remover_aluno();// removendo aluno do vector alunos
void remover_disciplina();// removendo disciplina do vector disciplina
void disciplinas_do_aluno();//quais disiciplina aquele aluno cursa
void alunos_da_disciplina();//quais alunos estao cadastrados naquela disciplina
void Lista_periodo();//mostra quais alunos e disciplinas estao cadastrados naquele periodo
void lista_de_alunos_disciplinas();//mostra todos os alunos e disciplinas cadastradas

//Criando os vector's que armazenarao dinamicamente os dados pedidos
vector <Aluno> alunos;
vector <Disciplina> disciplinas;
vector <Matricula> matriculas;//vector que vai unir as informaçoes do aluno com a da disciplina e acoplar em um periodo.
vector<string> verificacaoaluno;//vector que servirá de copia para retirar repetiçoes de alunos que fazem mais de uma disciplina no periodo para listagem, sem retirar do vector que sera salvo no arquivo.
vector<string> verificacaodisciplina;//similar ao anterior, porem para disciplinas.

int main(){
    int opcao=0;
    char a='s';
    carregamentodados();
    inicio:
    inicializacao();
    cout<< "\t\t\tOla, seja bem vindo!\n"<< "Digite a sua opcao:\n ";
    cin >> opcao;
    switch(opcao){
        case 1:
            cout<<"\nVoce escolheu a opcao de insercao de aluno:\n Para isso, siga os comandos a seguir.\n";
            inserir_aluno();
            break;
        
        case 2:
            cout<<"\nVoce escolheu a opcao de remocao de aluno:\n Para isso, siga os comandos a seguir.\n";
            remover_aluno();
            break;
        
        case 3:
            cout<<"\nVoce escolheu a opcao de insercao de disciplina:\n Para isso, siga os comandos a seguir.\n";
            inserir_disciplina();
            break;

        case 4:
            cout<<"\n Voce escolheu a opcao de remocao de disciplina:\n Para isso, siga os comandos a seguir.\n";
            remover_disciplina();
            break;

        case 5:
            cout<<"\nVoce escolheu a opcao de matricular um aluno em alguma disciplina:\nPara isso, siga os comandos a seguir.\n";
            realizar_matricula();
            break;
        case 6:
            cout<<"\nVoce escolheu a opcao de desmatricular um aluno de alguma disciplina:\nPara isso, siga os comandos a seguir.\n";
            remover_matricula();
            break;
        case 7:
            cout<<"\nVoce escolheu a opcao de ver quais alunos estao matriculados nessa disciplina\n";
            alunos_da_disciplina();
            break;

        case 8:
            cout<<"\nVoce escolheu a opcao de ver quais disciplinas esse aluno cursa \n";
            disciplinas_do_aluno();
            break;
        case 9:
            cout<< "\nAqui esta a lista cadastrada ate agora:\n \n";
            lista_de_alunos_disciplinas();
            break;
        case 10:
            cout<<"\nVoce escolheu a listagem de alunos e disciplinas por periodo:\n";
            Lista_periodo();
            break;
        case 0:
            cout<<"\nVoce escolheu encerrar o programa!\n";
            cout<< "\n\t\tSalvando os dados inseridos...\n";
            cout<<"\nDados salvos! Programa encerrado.\n";
            arquivo_de_dados();
            return 0;
    }
    arquivo_de_dados();
    cout<<"\nVoce quer voltar ao menu?S/N\n";
    cin>> a;
    if(a=='s'|| a=='S')
        goto inicio;
    else 
        cout<<"\nPrograma Encerrado.";
        cout<<"\nALTERACOES SALVAS!\n";
        return 0;

}


void arquivo_de_dados(){
    ofstream arquivo("Dados.txt");//abertura de arquivo para escrita
    arquivo << "Alunos Cadastrados:\n";
    for(const Aluno& aluno : alunos)/*definimos a variavel aluno que representara cada elemento do vector aluno, auto defini automaticamente
    o tipo de variavel e o const é pra nao altera-la durante o loop*/
    {
        arquivo << aluno.codigoA << "\n" << aluno.nomeA<<"\n"<< aluno.CPF <<"\n";}

    arquivo<< "Disciplinas Cadastradas:\n";
    for(const Disciplina& disciplina : disciplinas){
       
        arquivo << disciplina.codigoD << "\n"<< disciplina.nomeD << "\n"<< disciplina.professor<<"\n"<< disciplina.credito<< "\n";}

    arquivo<< "Matriculas feitas:\n";
    for(const Matricula& matricula : matriculas){
       
        arquivo<< matricula.codigo_aluno << "\n"<< matricula.codigo_disciplina << "\n"<< matricula.periodo << "\n";
}
arquivo.close();
}

void carregamentodados() {
    ifstream arquivo("Dados.txt");//abertura de arquivo para leitura
    if (!arquivo.is_open()) {
        return;
    }

    string linha;
    while (getline(arquivo, linha))//lendo o arquivo armazenando uma string
     {
        if (linha == "Alunos Cadastrados:") {
            
            cout<< "\nAlunos ate agora:(Codigo, nome, CPF)\n";}
            while (getline(arquivo, linha) && linha != "Disciplinas Cadastradas:") {
            
                Aluno aluno;
                aluno.codigoA = stoi(linha);
                getline(arquivo, linha);
                aluno.nomeA = linha;
                getline(arquivo, linha);
                aluno.CPF = linha;
                cout << aluno.codigoA << ' ' << aluno.nomeA << ' ' << aluno.CPF << '\n';
                alunos.push_back(aluno);
                
            }
        if (linha == "Disciplinas Cadastradas:") {
            
             cout<< "\nDisciplinas ate agora:(Codigo, nome, professor, creditos)\n";}
             while (getline(arquivo, linha) && linha != "Matriculas feitas:") {
            
                Disciplina disciplina;
                disciplina.codigoD = stoi(linha);
                getline(arquivo, linha);
                disciplina.nomeD = linha;
                getline(arquivo, linha);
                disciplina.professor = linha;
                getline(arquivo, linha);
                disciplina.credito = stoi(linha);
                cout << disciplina.codigoD << ' ' << disciplina.nomeD << ' ' << disciplina.professor << ' ' << disciplina.credito << '\n';
                disciplinas.push_back(disciplina);
            }
        if (linha == "Matriculas feitas:") {
            
            cout<< "\nMatriculas ate agora:(codigo do aluno, codigo da disciplina, periodo)\n";}
            if(arquivo.eof()){
            
                cout<<"Nao ha alunos matriculados\n\n";}
            while (getline(arquivo, linha)) {
            
                Matricula matricula;
                matricula.codigo_aluno = stoi(linha);
                getline(arquivo, linha);
                matricula.codigo_disciplina = stoi(linha);
                getline(arquivo, linha);
                matricula.periodo = linha;
                cout << matricula.codigo_aluno << ' ' << matricula.codigo_disciplina << ' ' << matricula.periodo << '\n';
             matriculas.push_back(matricula);
    }

    }

    arquivo.close();
}

void inicializacao(){
    cout<< " \n\t\t====== MENU ======\n\n";
    cout<<"1. Inserir Aluno................................"<< endl;
    cout<<"2. Remover Aluno................................" << endl;
    cout<<"3. Inserir Disciplina..........................."<< endl;
    cout<<"4. Remover Disciplina..........................."<< endl;
    cout<<"5. Realizar matricula..........................."<< endl;
    cout<<"6. Remover matricula............................"<< endl;
    cout<<"7. Alunos nessa disciplina......................"<< endl;
    cout<<"8. Disciplinas desse Aluno......................"<< endl;
    cout<<"9. Lista de alunos, disciplinas e matriculas....\n";
    cout<<"10. Listagem de alunos e disciplinas por periodo.\n";
    cout<<"0. Fechar o programa............................\n";
    cout<<"\n-----------------------------------------------------\n";
}

void inserir_aluno(){
    Aluno aluno;
    int codigo, a=0;
    bool codigoapto=true, CPFapto=true;
    string documento;
    while(!a){
        cout<< " Escreva o codigo do aluno:\n RESTRICAO: o codigo deve estar entre 10000 e 99999!\n";
        cin>> codigo;
        vector<Aluno>:: iterator i;
        for (i=alunos.begin(); i!=alunos.end(); i++){
            if(i->codigoA==codigo){
                cout<<"\nO aluno "<< i->nomeA<< " ja possui esse codigo, digite novamente.\n";
                a-=1;
                codigoapto=false;
                break;
            }}
        if(codigo>=10000 && codigo <100000 ){
            a+=1;
            if(codigoapto)
                aluno.codigoA=codigo;
        }
        else
            cout<<"Esse codigo e invalido, digite novamente.";
    }
    cout<<"\n Escreva o nome do aluno:\n";
    cin.ignore();
    getline(cin,aluno.nomeA);
    while(a){
        cout<< " Escreva o CPF do aluno:\n RESTRICAO: o CPF deve ser escrito da forma XXX.XXX.XXX-XX !\n";
        getline(cin,documento);
        vector<Aluno> :: iterator i;
        for( i=alunos.begin();i!=alunos.end();i++){
            if(i->CPF==documento){
                cout<< "\nEsses CPF pertence ao aluno "<<i->nomeA<<". Digite novamente.\n";
                a+=1;
                CPFapto=false;
                break;
            }
        }
        if(documento.length()!=14){
            cout<<"Esse codigo e invalido, digite novamente.";
        }
        else{
            a-=1;
            if(CPFapto)
                aluno.CPF=documento;
        }
    }
    
    alunos.push_back(aluno);
}

void inserir_disciplina(){
    Disciplina disciplina;
    int a=0, codigo;
    bool codigoapto=true;
    while(!a){
        cout<<" Escreva o codigo da disciplina:\n"<< "RESTRICAO: o codigo deve estar entre 1000 e 9999.\n";
        cin>> codigo;
        vector<Disciplina>:: iterator i;
        for (i=disciplinas.begin(); i!=disciplinas.end(); i++){
            if(i->codigoD==codigo){
                cout<<"\nA Disciplina "<< i->nomeD<< " ja possui esse codigo, digite novamente.\n";
                a-=1;
                codigoapto=false;
                break;
            }}
        if(codigo>=1000 && codigo <10000 ){
            a+=1;
            if(codigoapto)
                disciplina.codigoD=codigo;
        }
        else
            cout<<"Esse codigo e invalido, digite novamente.";
        }
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
    int codigoa, codigod;
    bool n=false;
    cout<<"\n Escreva o codigo do aluno que realizara a matricula:\n";
    cin>> codigoa;
    cout<<"\n Escreva o codigo da disciplina de matricula:\n";
    cin.ignore();
    cin >> codigod;
    vector<Matricula> :: iterator i;
    for( i=matriculas.begin(); i!=matriculas.end(); i++){
        if(i->codigo_aluno==codigoa && i->codigo_disciplina==codigod){
            cout<<"\nEsse aluno ja esta matriculado nessa disciplina.";
            n=true;}
    }
    if(!n){
        matricula.codigo_aluno=codigoa;
        matricula.codigo_disciplina=codigod;
        cout<<"\n Escreva o periodo de matricula da forma: ano semestre\n EX:2018.2 \n";
        cin.ignore();
        getline(cin, matricula.periodo);
        matriculas.push_back(matricula);
    }
}

void remover_aluno(){
    int codigo=0;
    bool n=false, matriculaacabou=false;
    cout<<"\nDigite o codigo do aluno que sera removido:\n";
    cin>> codigo;
    vector<Matricula>:: iterator j;
    for( j= matriculas.begin(); j!=matriculas.end();){
        if(j->codigo_aluno == codigo)
        {   matriculaacabou=true;
           j= matriculas.erase(j);}
        else 
            j++;}
    if(matriculaacabou)
        cout<<"Esse alunos estava cursando algumas disciplinas.\n";
    vector<Aluno> :: iterator i;
    for( i= alunos.begin(); i!=alunos.end();)//criando ima variavel i do tipo do elemento de alunos e vasculhando o vector do inicio ao fim
        {
        if(i->codigoA == codigo)//i está toamndo o valor de cada elemento do vetor e apontando pra o odigo daquela struct
        {   n=true;
            i=alunos.erase(i);
            cout<<"Aluno de codigo " <<codigo << " removido\n";
        }
        else
            i++;
    }
    if(!n){
    cout<< "\nAluno nao encontrado.\n";}
}

void remover_disciplina(){
    int codigo=0;
    bool n=false, matriculaacabou=false;
    cout<<"\nDigite o codigo da disciplina que sera removida:\n";
    cin>> codigo;
    vector<Matricula>:: iterator j;
    for( j= matriculas.begin(); j!=matriculas.end();){
        
        if(j->codigo_disciplina == codigo){
            
            matriculaacabou=true;
            matriculas.erase(j);}
        else 
            
            j++;}
    if(matriculaacabou)
         cout<<"Havia alunos matriculados nessa disciplina.\n";
    vector<Disciplina>::iterator i;
    for( i= disciplinas.begin(); i!=disciplinas.end();){
       
        if(i->codigoD == codigo)
        {  
            n=true;
            i= disciplinas.erase(i);
            cout<<"Disciplina de codigo " <<codigo << " removida.\n";
        }
        else
        i++;
    }
    if(!n){
    
        cout<<"\n Disciplina nao encontrada.\n";}
    else
    
        cout<<"Prosseguindo.. \n";
    }

void disciplinas_do_aluno(){
    
    int z=0, codigo;
    string per;
    bool alunoencontrado=false;
    cout<<"\nDigite o codigo do aluno:\n";
    cin>> codigo;
    cout<<"\nDigite o periodo em que o aluno esta:\n";
    cin>>per;
    cout<<"\nEssas sao as disciplinas que esse aluno esta cursando nesse periodo:\n";
    vector<Matricula>::iterator i;
    for( i= matriculas.begin(); i!=matriculas.end(); i++){
    
        if(i->codigo_aluno  == codigo && i->periodo == per){
    
            alunoencontrado=true;
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
    
        cout << "\nEsse aluno nao esta cursando disciplinas nesse periodo!\n";   
    }
}

void alunos_da_disciplina(){
    
    int z=0, codigo;
    string per;
    bool disciplinaencontrada=false;
    cout<<"\nDigite o codigo da disciplina:\n";
    cin>> codigo;
    cout<<"\nDigite o periodo em que essa disciplina esta sendo aplicada:\n";
    cin>> per;
    cout<<"\nEsses sao os alunos que estao matriculados nessa disciplina:\n";
    vector<Matricula>::iterator i;
    for(i= matriculas.begin(); i!=matriculas.end(); i++){
    
        if(i->codigo_disciplina==codigo && i->periodo == per){
    
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
    
        cout << "\nEssa disciplina nao esta sendo ministrada nesse periodo\n";
    }
}
void Lista_periodo(){
    
    string per;
    Aluno aluno;
    Disciplina disciplina;
    int a=0, d=0;
    bool periodoencontrado=false , alunoencontrado=false, disciplinaencontrada=false;
    cout<<"\nEscolha o periodo para ser listado:(EX: Ano.Semestre)\n";
    cout<<"\nAlunos matriculados no periodo :"<< endl;
    cin>>per;
    cout<< "\t\t\tPERIODO: "<<per<<endl;
    vector<Matricula>:: iterator i;
    for( i=matriculas.begin();i!=matriculas.end(); i++){
       
        if(i->periodo == per){
            
            periodoencontrado=true;
            vector<Aluno> :: iterator j;
            for(j=alunos.begin(); j!=alunos.end();j++){
                
                if(i->codigo_aluno == j->codigoA){
                   
                    alunoencontrado=true;
                    verificacaoaluno.push_back(j->nomeA);    
                }
            }
            if(!alunoencontrado){
                
                cout<<"\nNao ha aluno cadastrado com esse codigo!\n"; 
            }}}
    vector<string>:: iterator k;
    vector<string>:: iterator verificacaounica1 = unique(verificacaoaluno.begin(), verificacaoaluno.end());
    verificacaoaluno.erase(verificacaounica1, verificacaoaluno.end());
    for(k=verificacaoaluno.begin(); k!=verificacaoaluno.end() ;k++){
        
        a+=1;
        cout<<a<<"." <<*k<< "\n"; }
    cout<<"\nDisciplinas matriculadas nesse periodo::"<< endl;
    for( i=matriculas.begin();i!=matriculas.end(); i++){
        
        if(i->periodo == per){
        
            disciplinaencontrada=true;
            vector<Disciplina> :: iterator k;
            for(k=disciplinas.begin(); k!=disciplinas.end(); k++){
        
                if(i->codigo_disciplina == k->codigoD){
        
                    disciplinaencontrada=true;
                    verificacaodisciplina.push_back(k->nomeD);
                }
            }
            if(!disciplinaencontrada){
        
                cout << "\nNao ha disciplina cadastrada com esse codigo!\n";}
        }}
    vector<string>:: iterator l;
    vector<string>:: iterator verificacaounica2 = unique(verificacaodisciplina.begin(), verificacaodisciplina.end());//colocando elementos reptidos pro final do vetor
    verificacaodisciplina.erase(verificacaounica2, verificacaodisciplina.end());//apagando elementos repetidos.
    for(l=verificacaodisciplina.begin(); l!=verificacaodisciplina.end() ;l++){
        
        d+=1;
        cout<<d<<"." <<*l<< "\n"; }
    
    if(!periodoencontrado){
        
        cout << "\nNao ha esse periodo na faculdade!\n"; 
    }}

void lista_de_alunos_disciplinas(){
    
    int a=0, d=0,m=0;
    vector<Aluno> :: iterator i;
    cout<<"\t\t\t ALUNOS: \n";
    for(i=alunos.begin();i!=alunos.end();i++){
        
        a+=1;
        cout<<a<<'.'<< i->nomeA<< ' '<< i->codigoA<< ' '<< i->CPF<< endl;
    }
    cout<< "\t\t\t DISCIPLINAS:\n";
    for(vector<Disciplina>::iterator j=disciplinas.begin(); j!=disciplinas.end(); j++){
        
        d+=1;
        cout<<d<<'.'<< j->nomeD<< ' '<< j->codigoD<< ' '<< j->professor<< ' '<< j->credito<< endl;
    }
    cout<< "\t\t\t MATRICULAS:\n";
    for(vector<Matricula>::iterator k=matriculas.begin(); k!=matriculas.end(); k++){
       
        m+=1;
        cout<<m<<'.'<< k->codigo_aluno<< ' '<< k->codigo_disciplina<< ' '<< k->periodo<< endl;
    }
}

void remover_matricula() {
    int codigoa, codigod;
    string per;
    bool n=false;
    cout<<"\nDigite o codigo do aluno sera desmatriculado:\n";
    cin>>codigoa;
    cout<<"\nDigite o codigo da disciplina a qual o aluno sera desmatriculado:\n";
    cin>>codigod;
    cout<<"\nDigite o perido no qual o aluno ta matriculado:\n";
    cin>>per;
    vector<Matricula> :: iterator i;
    for( i= matriculas.begin(); i!=matriculas.end();)
        {
        if(i->codigo_aluno == codigoa && i->codigo_disciplina==codigod && i->periodo==per)//i está toamndo o valor de cada elemento do vetor e apontando pra o odigo daquela struct
        {   n=true;
            i=matriculas.erase(i);
            cout<<"Aluno de codigo " <<codigoa << " foi desmatriculado da disciplina de codigo "<<codigod<<" no periodo "<<per<< endl;
        }
        else
            i++;
        }
    if(!n){
        cout<< "\nEssas informacoes nao correspondem a nenhuma matricula no nosso registro. Tente novamente\n";}

}

