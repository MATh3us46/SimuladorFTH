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

int main(){
    queue<Prioridade> emergencia, urgencia, pouco_urgente, nao_urgente;
    char operacao;
    int v = 0, a = 0, d = 0, b = 0, atend = 0;
    int tv = 0, ta = 0, td = 0, tb = 0;
    int tal = 0, pc = 0;
    int espera_maxima = 0;
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
            int tempo_atual = converterParaMinutos(hora, minuto);
            bool atendeu = false;

            if(!emergencia.empty()){
                Prioridade p = emergencia.front();
                int tempo_chegada = converterParaMinutos(p.hora, p.minuto);
                int espera = tempo_atual - tempo_chegada;
                if(espera > espera_maxima) espera_maxima = espera;

                emergencia.pop();
                atend++;
                v--;
                tal--;
                atendeu = true;
            }
            else if(!urgencia.empty()){
                Prioridade p = urgencia.front();
                int tempo_chegada = converterParaMinutos(p.hora, p.minuto);
                int espera = tempo_atual - tempo_chegada;
                if(espera > espera_maxima) espera_maxima = espera;

                urgencia.pop();
                atend++;
                a--;
                tal--;
                atendeu = true;
            }
            else if(!pouco_urgente.empty()){
                Prioridade p = pouco_urgente.front();
                int tempo_chegada = converterParaMinutos(p.hora, p.minuto);
                int espera = tempo_atual - tempo_chegada;
                if(espera > espera_maxima) espera_maxima = espera;

                pouco_urgente.pop();
                atend++;
                d--;
                tal--;
                atendeu = true;
            }
            else if(!nao_urgente.empty()){
                Prioridade p = nao_urgente.front();
                int tempo_chegada = converterParaMinutos(p.hora, p.minuto);
                int espera = tempo_atual - tempo_chegada;
                if(espera > espera_maxima) espera_maxima = espera;

                nao_urgente.pop();
                atend++;
                b--;
                tal--;
                atendeu = true;
            }
            else{
                cout << hora << " " << minuto << " Sem pacientes aguardando atendimento" << endl;
            }
        }
        else if(operacao == 'D'){ //pacientes na fila agora
            cout << "V:" << v << " A:" << a << " D:" << d << " B:" << b << " | Atendidos:" << atend << endl;
        }
        else if(operacao == 'Q'){
            cout << "--- RELATORIO FINAL ---" << endl;
            cout << "Total atendidos:" << atend << endl; //quantos foram atendidos == quantos sairao da fila
            cout << "Por prioridade:V=" << tv << " A=" << ta << " D=" << td << " B=" << tb<< endl; //pacientes na fila total
            cout << "Pico de lotacao:" << pc << endl; //o maximo de pessoas que tiverao que ficar esperando
            cout << "Espera maxima: " << espera_maxima << endl;
            break;
        }
    }

    return 0;
}