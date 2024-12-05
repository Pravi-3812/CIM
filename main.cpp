#include <iostream>
#include<cmath>
#include <bits/stdc++.h>

using namespace std;
bool isequal (vector<vector<double>> matrix1 , vector<vector<double>> matrix2)
{
   for(int i = 1 ; i<matrix1.size() ; i++)
   for(int j = 1 ; j < matrix1[0].size() ; j++){
    if(matrix1[i][j] != matrix2[i][j])
        return false ;
   }
   return true ;
}
bool descend(const pair<int,double> &a,
                   const pair<int,double> &b)
{
       return a.second>b.second;
}


double rowsum( vector<vector<double>> matrix , int k )
{
    double sum = 0 ;
    int m = matrix[k].size() ;
    for (int i=1 ; i<m ; i++)
    {
        sum+= matrix[k][i] * pow(2,m-i-1) ;
    }
    return sum ;

}
double columsum (vector<vector<double>> matrix , int column)
{
    double sum = 0 ;
    int rows = matrix.size() ;
    for(int i = 1 ; i <rows ; i++)
    {
        sum+=matrix[i][column]*pow(2,rows -i - 1) ;
    }
    return sum ;

}
void rowsort(vector<vector<double>> &matrix)
{
    int row = matrix.size() ;
    for(int i = 1 ; i<row ; i++)
    {
        for(int j = 1+i ; j<row ; j++)
        {
            if(rowsum(matrix,j) > rowsum(matrix , i))
            {
                for(int k = 0 ; k < matrix[0].size() ; k++ )
                {
                   double temp = matrix[i][k] ;
                    matrix[i][k] = matrix[j][k] ;
                    matrix[j][k] = temp ;
                }
            }
        }
    }

}
void columsort(vector<vector<double>> &matrix)
{
    int colum = matrix[0].size() ;
    for(int i = 1 ; i<colum ; i++)
    {
        for(int j = 1+i ; j<colum ; j++)
        {
            if(columsum(matrix,j) > rowsum(matrix , j))
            {
                for(int k = 0 ; k < matrix.size() ; k++ )
                {
                   double temp = matrix[k][i] ;
                    matrix[k][i] = matrix[k][j] ;
                    matrix[k][j] = temp ;
                }
            }
        }
    }

}


vector <vector <double>> mcluster()
{
    int n,m ;
    cin>>n>>m ;
    vector<vector <double>> matrix(n+1,vector<double>(m+1,0)) ;
    matrix[0][0] = 0 ;
    for(int i = 1 ; i<=n ; i++)
        matrix[i][0] = i ;
    for(int i = 1 ; i<=m ; i++)
        matrix[0][i] = i ;
    for(int i = 1 ; i<=n ; i++)
    {
     for(int j =1 ; j<=m; j++) {
            double k ;
            cin>>matrix[i][j] ; }
     cout<<endl  ;
    }
  vector<vector<double>> matrix2 = matrix ;
  rowsort(matrix)  ;
  columsort(matrix) ;
  while (isequal(matrix2 , matrix) == false )
  {
      matrix2 = matrix ;
      rowsort(matrix) ;
      columsort(matrix) ;
  }
  return matrix ;
}
class machinesequence
{
private:
    int ko ;
    vector<pair<int,double>> fromratio  ;
    vector<vector<double>> fromto ;
    //unordered_map<int i , pair<int,int>> maps  ;


    public:

machinesequence()
    {
    int n ;
    cin>>n ;
    this->ko = n ;
    vector<vector <double>> A(n,vector<double>(n,0))  ;
    for(int i = 0 ; i<n ; i++)
        {
        for(int j = 0 ; j<n ; j++)
        cin>>A[i][j] ;
        cout<<endl ;
        }
    this->fromto = A ;
    vector<pair<int,double>> ratios ;
    for(int i = 0 ; i<n ; i++)
        {
        int from = 0, to = 0 ;
        double ratiof = 0.0  ;
        for(int j=0 ; j<n ; j++)
            from+= A[i][j] ;
        for(int k = 0 ; k<n ; k++)
        to+= A[k][i] ;
  //      this->maps[i] = make_pair(from,to)  ;
        if(to == 0)
        {
            ratiof = INT_MAX ;
        } else {
            ratiof = from / to  ;
        }
             ratios.push_back(make_pair(i,ratiof))  ;
       }

 sort(ratios.begin() , ratios.end() , descend) ;
 this->fromratio = ratios ;


}

vector<double> productionanalysis()
{
    int countr = 0;
    vector<double> sequence(ko,0) ;
    for(auto i: fromratio){
      sequence[countr] = i.first ;
      countr++ ;
    }
int insequence = 0 , backtracking = 0 , bypassing = 0 , tot ;
for(int i = 0 ; i< ko-1 ; i++ )
{
    insequence+= fromto[sequence[i]][sequence[i+1]] ;

}
for(int i =1 ; i<ko ; i++)
{
    for(int j = i-1 ; i>=0 ; i--)
        backtracking+= fromto[sequence[i]][sequence[j]] ;
}
for(int i=0 ; i<ko-2 ; i++)
{
    for(int j = i+2 ; j< ko ; j++)
        bypassing+= fromto[sequence[i]][sequence[j]] ;
}
for(int i = 0 ; i<ko ; i++)
for(int j = 0 ; j<ko ; j++)
tot+= fromto[i][j] ;
double insperc = bypassing/tot ,backperc = backtracking/tot , bypassperc = bypassing/tot ;
vector<double> r(3,0) ;
r[0] =  insperc;
r[1] =   backperc;
r[2] =    bypassperc;
return r ;
}
} ;


int main()
{
 vector<vector<double>> A =   mcluster()  ;
 for(int i =  0 ; i< A.size() ; i++){
    for(int j = 0 ; j<A[0].size() ; j++ )
        cout<<A[i][j]<<"   ";
        cout<<endl ;

    }

    return 0;
}
