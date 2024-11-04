# robotica_an3_tema2


## Descriere Generală
Acest proiect Arduino implementează un joc de tastat care consta în introducerea literelor unui cuvânt afișat pe Serial Monitor, într-un interval de timp limitat. 

Jocul include trei niveluri de dificultate care ajustează timpul permis pentru a tasta fiecare cuvânt.

Utilizatorul controlează jocul prin două butoane – unul pentru a porni/opri jocul și altul pentru a schimba nivelul de dificultate. 

LED-uri sunt folosite pentru a indica starea jocului:

- LED-ul roșu se aprinde la o tastare incorectă,
- LED-ul verde indică progresul corect al jocului,
- LED-ul pâlpâie alb în timpul unei numărători inverse la începutul fiecărei runde.

Dicționarul jocului conține o listă de cuvinte prestabilite care sunt afișate în ordine aleatorie.
În fiecare rundă, utilizatorul trebuie să tasteze literele fiecărui cuvânt într-un timp limitat, obținând puncte pentru fiecare cuvânt completat corect.



## Componente
- Arduino UNO (ATmega328P microcontroller)
- 1x LED RGB (pentru a semnaliza dacă cuvântul corect e scris greșit sau nu)
- 2x Butoane (pentru start/stop rundă și pentru selectarea dificultății)
- 5x Rezistoare (3x 220 ohm, 2x 2000 ohm)
- Breadbord
- Fire de legătură

## Poze ale setup-ului fizic

![WhatsApp Image 2024-11-04 at 19 26 23_36225193](https://github.com/user-attachments/assets/b7bc3da7-7e01-4420-9e6e-1da8d1cc91e8)
![WhatsApp Image 2024-11-04 at 19 26 23_32ca9ec9](https://github.com/user-attachments/assets/c1f84788-5673-4ce6-ab09-45b706ffccda)
![WhatsApp Image 2024-11-04 at 19 26 22_c8365b3d](https://github.com/user-attachments/assets/68209922-db52-43e0-8428-86f143447c4f)
![WhatsApp Image 2024-11-04 at 19 26 22_b93148c1](https://github.com/user-attachments/assets/cd3bcae2-7a9d-4d8f-be45-1de459f446bd)


## Video cu functionalitatea montajului fizic
[Watch video here!](https://youtu.be/372jr29r4Q4)


