# benchmark-devforum
Generator de numere aleatoare si proof-of-concept pentru bechmark
------------------------

Aplicatia "generator" va citi "/dev/urandom" si va genera 100,000,000 perechi de numere cu 4 zecimale aleatoare. Perechile de numere vor fi impartite, iar rezultatul (rotunjit la 8 zecimale), impreuna cu deimpartitul si impartitorul,  va fi scris in fisierul "random_numbers.txt".

------------------------

Aplicatia "benchmark" este un proof-of-concept cu ce trebuie sa faca benchmark-ul. Si anume, sa citeasca valorile din "random_numbers.txt", sa le imparta, si la fel ca "generatorul", sa le scrie in fisierul "result.txt". In final, md5sum-urile (random_numbers.txt si result.txt) celor doua fisiere ar trebui sa fie identice.

------------------------

Scopul acestui benchmark este sa vedem diferentele de performanta dintre limbajele de programare, si, eventual, sa invatam cum sa "stoarcem" tot ce putem din ele.
