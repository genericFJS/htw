int bsearch (int a[], int n, int val){
    if (n == 0){
        return 0;
    }
    if (a[n/2]== val){
        return 1;
    } else if (val < a[n/2]){
        return bsearch(a,n/2-1,val);
    } else{
        return bsearch(a+(n/2)+1,n-n/2-1),val);
    }
}