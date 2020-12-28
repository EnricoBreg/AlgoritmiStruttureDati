Modifiche effettuate a:
	LISTE COLLEGATE:
		- modificata la funzione linkedListDelete con un controllo sul nodo da eliminare. Controllo aggiunto per evitare Segmentation Fault nell'accedere ad un area di memoria definita NULL;
		- aggiunto un controllo del secondo if statement di LinkedListDelete, ora prima di controllare il valore di x->next->prev controlla anche che effettivamente x->next non sia NULL, per evitare Segmentation Fault;
		- Aggiunto incremento automatico della dimensione della lista in listInsert;
		- Aggiunto decremento automatico della dimensione della lista in linkedListDelete;
