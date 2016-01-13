void mergesort(int a[], int n){	
	if (n>1){
		int a1[n/2];
		int a2[n-n/2];
		copy(a1,a,n/2);
		copy(a2,a+n/2,n-n/2);
		mergesort(a1,n/2);
		mergesort(a2,n-n/2);
		merge(a,a1,n/2,a2,n-n/2);
	}
}

void quicksort(int a[], int n){
	if(n>1){
		p = partition(a,n);
		quicksort(a,p);
		quicksort(a+p+1,n-p-1));
	}
}

// Idee:
int myPartition(int a[], int n){
	int old[n];
	int i;
	int pivot=0;
	int lec=0;
	int gec=0;
	memcpy(old[], a[], n);
	for (i=1; i<n; i++){
		if(a[i]<a[0]){
			pivot++;
		}
	}
	for (i=1;i<n;i++){
		if(a[i]<a[0]){
			a[lec]=old[i];
			lec++;
		} else {
			a[pivot+gec]=old[i];
			gec++;
		}
	}
	return pivot;
}

// Lösung:
int partition(int a[], int n){
	int p=a[0];
	int i,j,k; i=0; j=n-1;
	int b[n];
	for (k=1; k<n; k++){
		if(a[k]<p){
			b[i++]=a[k];
		} else {
			b[j--]=a[k];
		}
	}
	// nachdem alle größeren und kleineren einsortiert sind, noch das Pivotelement selber einsortieren:
	b[i]=p;
	for (k=0;k<n;k++){
		a[k]=b[k];
	}
	return i;
}