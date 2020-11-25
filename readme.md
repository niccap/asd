# Algoritmi e Strutture Dati

Questo repository include parte del codice utilizzato a lezione per l'insegnamento di  __Algoritmi e Strutture Dati__ del corso di laurea in Ingegneria Informatica dell'Università di Salerno.

Istruzioni per la compilazione degli esercizi: 
```
gcc esercizi/eserciziList.c strutture/TList.c strutture/TInfo.c
gcc esercizi/eserciziArrayList.c strutture/TList.c strutture/TArray.c strutture/TInfo.c
gcc esercizi/eserciziCodeStack.c strutture/TQueue.c strutture/TStack.c strutture/TArray.c strutture/TInfo.c
gcc esercizi/eserciziBST.c strutture/TBST.c strutture/TInfo.c
gcc esercizi/eserciziHT.c strutture/THT/THT.c strutture/THT/TInfo.c strutture/THT/TList.c
```

Istruzioni per la compilazione del codice di esempio sugli algoritmi di base: 
```
gcc algoritmi/ricerca.c strutture/TInfo.c
gcc algoritmi/ordinamento.c strutture/TInfo.c
```

__N.B.__: le strutture dati _THT_ e _THTopen_ si trovano nella sottocartella _strutture/THT_ poiché necessitano di una diversa versione del tipo _TInfo_ rispetto a quallo contenuto nella catella _strutture_.

---
_[DIEM](https://www.diem.unisa.it/) - Università di Salerno_