#include <iostream>
#include <queue>

using namespace std;

struct Prioridade{
    string senha;
    char prioridade;
    int hora;
    int minuto;
};

void addpaciente(queue<Prioridade>& fila, int& qtd_atual, int& qtd_total, const Prioridade& p){
    fila.push(p);
    qtd_atual++;
    qtd_total++;
    cout << "Paciente inserido com sucesso" << endl;
}

int converterParaMinutos(int hora, int minuto){
    return hora * 60 + minuto;
}

int main(){
    queue<Prioridade> emergencia, urgencia, pouco_urgente, nao_urgente;
    char operacao;
    int v = 0, a = 0, d = 0, b = 0, atend = 0;
    int tv = 0, ta = 0, td = 0, tb = 0;
    int tal = 0, pc = 0;
    int espera_maxima = 0;
    while(true){
        Prioridade paciente;
        cout << "Escolha uma opcao:" << endl;
        cout << "'C' - Cadastrar entrada de paciente" << endl;
        cout << "'A' - Atender paciente" << endl;
        cout << "'D' - Exibir status das filas" << endl;
        cout << "'Q' - Encerrar e exibir o relatorio final" << endl;
        cin >> operacao;
        if(operacao == 'C'){
            cout << "Digite a senha, a prioridade('V','A','D','B'), a hora e o minuto" << endl;
            cin >> paciente.senha >> paciente.prioridade >> paciente.hora >> paciente.minuto;
            bool prioridade_valida = true;

            if(paciente.prioridade == 'V'){
                addpaciente(emergencia, v, tv, paciente);
            }
            else if(paciente.prioridade == 'A'){
                addpaciente(urgencia, a, ta, paciente);
            }
            else if(paciente.prioridade == 'D'){
                addpaciente(pouco_urgente, d, td, paciente);
            }
            else if(paciente.prioridade == 'B'){
                addpaciente(nao_urgente, b, tb, paciente);
            }
            else{
                cout << "Prioridade invalida" << endl;
                prioridade_valida = false;
            }

            if(prioridade_valida){
                tal++;
                if(tal > pc){
                    pc = tal;
                }
            }
        }
        else if(operacao == 'A'){
            int hora, minuto;
            cout << "Informe a hora e o minuto do atendimento:" << endl;
            cin >> hora >> minuto;
            int tempo_atual = converterParaMinutos(hora, minuto);

            if(!emergencia.empty()){
                Prioridade p = emergencia.front();
                int tempo_chegada = converterParaMinutos(p.hora, p.minuto);
                int espera = tempo_atual - tempo_chegada;
                if(espera > espera_maxima){
                    espera_maxima = espera;
                }

                emergencia.pop();
                atend++;
                v--;
                tal--;
                cout << "Paciente da prioridade V atendido." << endl;
            }
            else if(!urgencia.empty()){
                Prioridade p = urgencia.front();
                int tempo_chegada = converterParaMinutos(p.hora, p.minuto);
                int espera = tempo_atual - tempo_chegada;
                if(espera > espera_maxima){
                    espera_maxima = espera;
                }

                urgencia.pop();
                atend++;
                a--;
                tal--;
                cout << "Paciente da prioridade A atendido." << endl;
            }
            else if(!pouco_urgente.empty()){
                Prioridade p = pouco_urgente.front();
                int tempo_chegada = converterParaMinutos(p.hora, p.minuto);
                int espera = tempo_atual - tempo_chegada;
                if(espera > espera_maxima){
                    espera_maxima = espera;
                }

                pouco_urgente.pop();
                atend++;
                d--;
                tal--;
                cout << "Paciente da prioridade D atendido." << endl;
            }
            else if(!nao_urgente.empty()){
                Prioridade p = nao_urgente.front();
                int tempo_chegada = converterParaMinutos(p.hora, p.minuto);
                int espera = tempo_atual - tempo_chegada;
                if(espera > espera_maxima){
                    espera_maxima = espera;
                }

                nao_urgente.pop();
                atend++;
                b--;
                tal--;
                cout << "Paciente da prioridade B atendido." << endl;
            }
            else{
                cout << "Horario " << hora << ":" << minuto << " - Nao ha pacientes aguardando." << endl;
            }
        }
        else if(operacao == 'D'){ 
            cout << "Fila: V=" << v << " A=" << a << " D=" << d << " B=" << b << " | Atendidos=" << atend << endl;
        }
        else if(operacao == 'Q'){
            cout << "--- RELATORIO FINAL ---" << endl;
            cout << "Total atendidos: " << atend << endl; 
            cout << "Por prioridade: V=" << tv << " A=" << ta << " D=" << td << " B=" << tb << endl; 
            cout << "Pico de lotacao: " << pc << endl; 
            cout << "Espera máxima: " << espera_maxima << " min" << endl;
            break;
        }
        else{
            cout << "Opcao invalida! Tente novamente." << endl;
        }
    }

    return 0;
}
