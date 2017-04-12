/* Leser-Schreiber-Problem, erneuter Versuch */
int sema_t mutex=1, readsleep=0, writesleep=0; 
int readwait=0, readcount=0, writewait=0;      

void reader(void)
{
  while(1) { 
      P(mutex);
      if (writewait > 0) {
          readwait++;
          V(mutex);
          P(readsleep);
      }
      else {
	  readcount++;
          V(mutex);
      }

      /* lesender Zugriff auf Datenbank */
    
      P(mutex);
      readcount--;
      if ((readcount==0)&&(writewait>0)) {
	  writewait--;
          V(writesleep);
      }
      else {
	  V(mutex);
      }
  }
}

void writer(void)
{
  while(1) {
      P(mutex);
      if (readcount>0) {
	  writewait++;
          V(mutex);
          P(writesleep);
      }

      /* schreibender Zugriff auf Datenbank */ 

      if (readwait>0) {
	  while(readwait>0) {
	      readwait--;
              readcount++;
              V(readsleep);
	  }
          V(mutex);
      }
      else if (writewait>0) {
	  writewait--;
          V(writesleep);
      }
      else {
	  V(mutex);
      }
  }
}
