class Fraction
{
    public:
    Fraction (){Numerator = 0; Denom = 1;};
    Fraction (long N){Numerator = N; Denom = 1;};
    Fraction ( long Num, long Den);
    void Display() const;
    Fraction operator+ (const Fraction & Second) const;
    Fraction& operator+= (const Fraction & Second);
    int operator<(const Fraction& other)
     { return (int) ((double)Numerator)/Denom -((double)other.Numerator)/other.Denom;}
    friend ostream& operator<<(ostream& OS,Fraction& F);
    private:
    static long gcf(long First,long Second);
    long Numerator,
	 Denom;
};
