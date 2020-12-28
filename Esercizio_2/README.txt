Modifiche effettuate a:
	LISTE COLLEGATE:
		- modificato il valore di ritorno di LinkedListDelete da void ad int per evitare che si elimini un nodo che non esiste;
		- aggiunto un controllo del secondo if statement di LinkedListDelete, ora prima di controllare il valore di x->next->prev controlla anche che effettivamente x->next non sia NULL, per evitare Segmentation Fault;
		- Aggiunto incremento automatico della dimensione della lista in listInsert
		- Aggiunto decremento automatico della dimensione della lista in linkedListDelete
