#include <iostream>
#include <queue>

using namespace std;

struct Prioridade{
    string senha;
    char prioridade;
    int hora;
    int minuto;
};

int main(){
    queue<Prioridade> emergencia, urgencia, pouco_urgente, nao_urgente;
    char operacao;
    int v = 0, a = 0, d = 0, b = 0, atend = 0;
    int tv = 0, ta = 0, td = 0, tb = 0;
    int tal = 0, pc = 0;
    while(true){
        Prioridade paciente;
        cin >> operacao;
        if(operacao == 'C'){
            cin >> paciente.senha >> paciente.prioridade >> paciente.hora >> paciente.minuto;
            if(paciente.prioridade == 'V'){
                emergencia.push(paciente);
                v++;
                tv++;
            }
            else if(paciente.prioridade == 'A'){
                urgencia.push(paciente);
                a++;
                ta++;
            }
            else if(paciente.prioridade == 'D'){
                pouco_urgente.push(paciente);
                d++;
                td++;
            }
            else if(paciente.prioridade == 'B'){
                nao_urgente.push(paciente);
                b++;
                tb++;
            }
            tal++;
            if(tal > pc){ 
                pc = tal;
            }
        }
        else if(operacao == 'A'){
            int hora, minuto;
            cin >> hora >> minuto;
            if(!emergencia.empty()){
                emergencia.pop();
                atend++;
                v--;
                tal--;
            }
            else if(!urgencia.empty()){
                urgencia.pop();
                atend++;
                a--;
                tal--;
            }
            else if(!pouco_urgente.empty()){
                pouco_urgente.pop();
                atend++;
                d--;
                tal--;
            }
            else if(!nao_urgente.empty()){
                nao_urgente.pop();
                atend++;
                b--;
                tal--;
            }
            else{
                cout << hora << " " << minuto << " Sem pacientes aguardando atendimento" << endl;
            }
        }
        else if(operacao == 'D'){
            cout << "V:" << v << " A:" << a << " D:" << d << " B:" << b << " | Atendidos:" << atend << endl;
        }
        else if(operacao == 'Q'){
            cout << "--- RELATORIO FINAL ---" << endl;
            cout << "Total atendidos:" << atend << endl;
            cout << "Por prioridade:V=" << tv << " A=" << ta << " D=" << td << " B=" << tb<< endl;
            cout << "Pico de lotacao:" << pc << endl;
            cout << "Espera máxima: " << 0 << endl;
            break;
        }
    }

    return 0;
}