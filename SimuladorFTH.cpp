#include <iostream>
#include <queue>

using namespace std;

struct Prioridade{
    string senha;
    char prioridade;
    int hora;
    int minuto;
};

int converterParaMinutos(int hora, int minuto){
    return hora * 60 + minuto;
}

void addpaciente(queue<Prioridade> &fila, int &qtd_atual, int &qtd_total, const Prioridade &p){
    fila.push(p);
    qtd_atual++;
    qtd_total++;
    cout << "Paciente inserido com sucesso" << endl;
}

bool atenderPaciente(queue<Prioridade> &fila, int &qtd_atual, int &atend, int &tal, int tempo_atual, int &espera_maxima){
    if(fila.empty()) {
        return false;
    }

    Prioridade p = fila.front();
    int tempo_chegada = converterParaMinutos(p.hora, p.minuto);
    int espera = tempo_atual - tempo_chegada;

    if(espera > espera_maxima){
        espera_maxima = espera;
    }

    fila.pop();
    atend++;
    tal--;
    qtd_atual--;

    cout << "Paciente atendido." << endl;

    return true;
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
        cout << "Escolha uma opcao:\nC - Cadastrar\nA - Atender\nD - Status\nQ - Relatório\n";
        cin >> operacao;

        if(operacao == 'C'){
            cout << "Digite: senha prioridade hora minuto\n";
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
            cout << "Informe hora e minuto:\n";
            cin >> hora >> minuto;

            int tempo_atual = converterParaMinutos(hora, minuto);

            if(atenderPaciente(emergencia, v, atend, tal, tempo_atual, espera_maxima)){}
            else if(atenderPaciente(urgencia, a, atend, tal, tempo_atual, espera_maxima)){}
            else if(atenderPaciente(pouco_urgente, d, atend, tal, tempo_atual, espera_maxima)){}
            else if(atenderPaciente(nao_urgente, b, atend, tal, tempo_atual, espera_maxima)){}
            else{
                cout << hora << " " << minuto << "Sem pacientes aguardando atendimento" << endl;;
            }
        }

        else if(operacao == 'D'){
            cout << "V=" << v << " A=" << a << " D=" << d << " B=" << b << " | Atendidos=" << atend << endl;
        }

        else if(operacao == 'Q'){
            cout << "--- RELATORIO FINAL ---";
            cout << "Total Atendidos: " << atend << endl;
            cout << "Por prioridade: V=" << tv << " A=" << ta << " D=" << td << " B=" << tb << endl;
            cout << "Pico de lotação: " << pc << endl;
            cout << "Espera máxima: " << espera_maxima << " min" << endl;
            break;
        }

        else{
            cout << "Opcao invalida!" << endl;
        }
    }

    return 0;
}