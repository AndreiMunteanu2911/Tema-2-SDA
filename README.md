# Tema-2-SDA
**Nume: Munteanu Andrei**
**Grupă: 315 CD**

## Tema 2 - Vigenere Cipher

### Descriere:

createTree: alocam memorie unei structuri TTree*, setam root NULL, size 0 si asociem toate functiile primite.
isEmpty: verificam daca tree->root este NULL sau nu.
search: verificam daca nodul primit este cel cautat. Daca nu, apelam recursiv functia in nodul stang si cel drept al celui curent, si verificam daca left sau right sunt NULL. Daca ambele sunt NULL inseamna ca nu s-a gasit elementul cautat.
minimum: mergem in nodul cel mai din stanga al arborelui.
maximum: mergem in nodul cel mai din dreapta al arborelui.
successor: Daca x->right nu e NULL, atunci succesorul e minimul din subarborele cu radacina in x->right. Altfel, succesorul e primul parinte al carui copil e la stanga.
predecessor: Daca x->left nu e NULL, atunci predecesorul e maximul din subarborele cu radacina in x->left. Altfel, succesorul e primul parinte al carui copil e la dreapta.
avlRotateLeft: in check1 memoram daca parintele lui x e nul sau nu pentru a-l putea conecta la y in urma rotatiei, si in lr memoral daca este copilul stang sau drept. In check2 memoram daca x este radacina lui tree sau nu. Apoi facem rotirea propriu-zisa, si, in functie de checkuri, schimbarile necesare.
avlRotateRight: in check1 memoram daca parintele lui y e nul sau nu pentru a-l putea conecta la x in urma rotatiei, si in lr memoral daca este copilul stang sau drept. In check2 memoram daca y este radacina lui tree sau nu. Apoi facem rotirea propriu-zisa, si, in functie de checkuri, schimbarile necesare.
