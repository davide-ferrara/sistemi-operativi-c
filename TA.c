/* 
    Un dipartimento di informatica ha un assistente (TA) che aiuta gli studenti universitari
    nei loro esercizi di programmazione, in orario d’ufficio. L’ufficio del TA è piuttosto
    piccolo e ha spazio solo per una scrivania con una sedia e per un computer. Ci sono
    tre sedie in corridoio, davanti all’ufficio, dove gli studenti possono sedersi e aspettare
    quando il TA è impegnato nell’aiuto a un altro studente. Quando non ci sono studenti
    che hanno bisogno di aiuto, il TA si siede alla scrivania e fa un pisolino. Se uno stu-
    dente arriva in orario d’ufficio e trova il TA che dorme, deve svegliarlo per chiedergli
    aiuto. Se uno studente arriva e trova il TA che sta aiutando un altro studente, si siede
    su una delle sedie in corridoio e aspetta. Se non ci sono sedie disponibili, lo studente
    dovrà tornare in un secondo momento.
    Utilizzando i thread POSIx, i lock mutex e i semafori implementate una soluzione
    per coordinare le attività del TA e degli studenti. Riportiamo di seguito i dettagli di
    questo progetto.

    Utilizzando Pthread (Paragrafo 4.4.1), iniziate dalla creazione di n studenti. Ogni stu-
    dente e il TA verranno eseguiti come thread distinti. I thread degli studenti alterne-
    ranno un periodo di tempo di programmazione alla ricerca di aiuto dal TA. Se il TA è
    disponibile, otterranno aiuto. In caso contrario, si siederanno su una sedia nel corri-
    doio o, se non ci sono sedie disponibili, riprenderanno l’attività di programmazione
    e cercheranno aiuto in un secondo momento. Se uno studente arriva e si accorge che
    il TA sta dormendo, deve notificare il suo arrivo al TA con un semaforo. Quando il TA
    finisce di aiutare uno studente deve controllare in corridoio per vedere se ci sono stu-
    denti in attesa di aiuto. In caso affermativo, il TA deve aiutare, a turno, tutti gli stu-
    denti. Se non sono presenti studenti, il TA può tornare a dormire.
    Probabilmente l’opzione migliore per simulare gli studenti che programmano e il
    TA che fornisce aiuto a uno studente è di sospendere i thread coinvolti per un periodo
    di tempo casuale.

*/

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

#define NUM_OF_STUDENTS 4
#define NUM_OF_TA 1
#define NUM_OF_CHAIRS 3


pthread_mutex_t mutex_TA; // Mutex per la scrivania TA
sem_t sem_sedie; // Semaforo per le sedie 
bool TA_sleeping = false;

void *TA_fn(void *args){
    pthread_mutex_lock(&mutex_TA);

    if(!TA_sleeping){
        if(sem_wait(&sem_sedie) == 0){
            sleep(5); // Aiuta uno studente
            sem_post(&sem_sedie);
        } else {
            printf("Non c'è nessuno studente nel corridoio, il TA adesso dormirà...\n");
            TA_sleeping = true;
        }

    } else {
        pthread_mutex_unlock(&mutex_TA);
        printf("Il TA sta dormendo...\n");
        sleep(5);
    }

}

void* student_fn(void* args){
    // Simula il tempo per programmare
    sleep(5);

    pthread_mutex_lock(&mutex_TA);

    if(!TA_sleeping){
        if (sem_trywait(&sem_sedie) == 0) {
            printf("Lo studente è seduto e aspetta il suo turno.\n");
            pthread_mutex_unlock(&mutex_TA);
            // Attendere fino a quando il TA non è disponibile
            sem_wait(&sem_sedie);
            printf("Lo studente è stato aiutato dal TA.\n");
        } else {
            printf("Non ci sono sedie disponibili nel corridoio. Lo studente tornerà più tardi.\n");
            pthread_mutex_unlock(&mutex_TA);
            // Non ci sono sedie disponibili, lo studente torna più tardi
            return NULL;
        }
    } else {
        TA_sleeping = true;
        // Sveglia il TA
        printf("Lo studente sveglia il TA!\n");
        sem_post(&sem_sedie);
    }
}

int main(int argc, char** agrv){
    
    pthread_t TA_td[NUM_OF_TA];
    pthread_t students_td[NUM_OF_STUDENTS];

    pthread_mutex_init(&mutex_TA, NULL);
    sem_init(&sem_sedie, 0, NUM_OF_CHAIRS);

    for(int i = 0; i < NUM_OF_TA; i++){
        if(pthread_create(&TA_td[i], NULL, TA_fn, NULL) != 0) return -1;
    }

    for(int i = 0; i < NUM_OF_STUDENTS; i++){
        if(pthread_create(&TA_td[i], NULL, student_fn, NULL) != 0) return -1;
    }

    for(int i = 0; i < NUM_OF_TA; i++){
        if(pthread_join(students_td[i], NULL) != 0) return -1;
    }

    for(int i = 0; i < NUM_OF_STUDENTS; i++){
        if(pthread_join(students_td[i], NULL) != 0) return -1;
    }

    pthread_mutex_destroy(&mutex_TA);
    sem_destroy(&sem_sedie);

    return 0;
}

