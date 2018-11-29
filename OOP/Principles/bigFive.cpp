class IntCell
2 {
3 public:
4 explicit IntCell( int initialValue = 0 )
5 { storedValue = new int{ initialValue }; }
67
~IntCell( ) // Destructor
8 { delete storedValue; }
9
10 IntCell( const IntCell & rhs ) // Copy constructor
11 { storedValue = new int{ *rhs.storedValue }; }
12
13 IntCell( IntCell && rhs ) : storedValue{ rhs.storedValue } // Move constructor
14 { rhs.storedValue = nullptr; }
15
16 IntCell & operator= ( const IntCell & rhs ) // Copy assignment
17 {
18 if( this != &rhs )
19 *storedValue = *rhs.storedValue;
20 return *this;
21 }
22
23 IntCell & operator= ( IntCell && rhs ) // Move assignment
24 {
25 std::swap( storedValue, rhs.storedValue );
26 return *this;
27 }
28
29 int read( ) const
30 { return *storedValue; }
31 void write( int x )
32 { *storedValue = x; }
33
34 private:
35 int *storedValue;
36 };
