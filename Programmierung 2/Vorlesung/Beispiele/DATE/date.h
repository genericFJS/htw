// A. Beck
// Beispiel zur Vorlesung PSP II


class date
{
  private:
   int Day;
   int Month;
   int Year;
  public:
   // Constructor
   date(int d, int m, int y);
   date();
   // Methoden
   void setDate (int d, int m, int y);

   void setDay  (int Day  ){this->Day  =Day;}
   void setMonth(int Month){this->Month=Month;}
   void setYear (int Year ){this->Year =Year;}
   
   int  getDay  ()const {return this->Day;}
   int  getMonth()const {return this->Month;}
   int  getYear ()const {return this->Year;}
   void display()const;
};
