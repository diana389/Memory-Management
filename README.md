In main, am folosit un while pentru a putea primi comenzi pana la intalnirea sirului "exit".
Se compara cuvantul citit si se compara cu cele 6 tipuri de comenzi, urmand sa se apeleze functia corespunzatoare.
In cazul "insert" si "insert_at", se declara o structura (new_data), care este completata prin functia "add_new_data", adaugata in vector si apoi eliberata.

add_new_data: 
Se adauga "type" in header, dupa care se citesc cele 2 siruri si cele 2 sume corespunzator tipului si se completeaza si variabila "len", care contine dimensiunea lui "data".
Datele se copiaza cu memcpy in "data".

add_last:
Am folosit len pentru memorarea dimensiunii vectorului "arr". In functie de caz, am aclocat sau realocat memorie (pentru "len" + dimensiunea datelor pe care urmeaza sa le introduc).
Am copiat cu memcpy datele din "header" si din "data" si am revenit cu arr in pozitia initiala. "len" creste cu dimensiunea datelor din structura.

add_at:
Am luat cazul in care indexul este mai mic decat 0, iar daca da am returnat 0. Am initializat "contor" cu 0 pentru a numara cate elemente sunt pana in pozitia curenta, dupa care am  parcurs vectorul, avand ca si conditie de oprire ori egalitatea dintre "contor" si "index", ori depasirea lungimii vectorului (prin variabila "currenr_len_arr"). Daca este indeplinita cea de-a doua conditie, datele se introduc la sfarsit, deci am apelat add_last, iar, daca nu am realocat memorie cat sa incapa si noile date si le-am copiat la fel ca in add_last, la "arr + current_len_arr", dupa ce am mutat toate datele urmatoare spre dreapta. 

find:
In mod asemanator am procedat in prima parte, mutand "arr" pe pozitia unde se incep datele
cautate si am apelat functia print pentru "elem_len" - dimensiunea elementului cautat, pentru
a il afisa doar pe acesta.

delete_at:
In mod asemanator am procedat si pentru aceasta functie pentru a afla "contor" si 
"current_len_arr" si pentru a verofoca cele doua cazuri (in care indexul este mai mic decat 0 
si in care depaseste numarul de elemente). Altfel, am copiat datele de dupa element spre stanga,
peste acesta, dupa care am realocat memorie tinand cont ca exista cu un element mai putin,
si am marcat acest lucru si micsorand "len".

print:
In aceasta functie am folosit un while, avand conditia de oprire sa nu se depaseasca lungimea
vectorului. In fiecare iteratie am parcurs elementul si am afisat datele acestuia, tinand 
cont de tipul sau si deplasand "arr"-ul. La sfarsit, am adus "arr" in pozitia initiala.
