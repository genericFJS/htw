int compare_and_swap2(T *loc1, T *loc2, T old1, T old2, T new1, T new2)
{
  <begin atomic>
  if ( (*loc1 == old1) && (*loc2 == old2) ){
    *loc1 = new1;
    *loc2 = new2;
    return TRUE;
  }
  else {
    return FALSE;	  
  }
  <end atomic>
}
