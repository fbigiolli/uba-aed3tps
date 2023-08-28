/*

ILI
#IL
+L+

+#
#L

LI+L
++IL
I#+#
LI++

*/

i j 
m[i][j] = true;
tuki()
m[i][j] = false;

dp[i][j][de_donde_vengo][a_donde_voy] =  

tuki(i,j,a,b,sumaCamino)
{

    if (dp[i][j][de_donde_vengo][a_donde_voy])
        return  dp[i][j][de_donde_vengo][a_donde_voy];
    else

    if(i == n - 1 && j == m-1) //llegue al final
    {
        true
        if tuki( ) < sumaMin 
            actualizo sumaMin
        else if sumaCamino > sumaMax
            actualizo sumaMax
    }

    if puedomoverme(i +1,j,n,n) || puedomoverme(i,j+1,n,m){
        if tuki([i][j][de_donde_vengo][a_donde_voy]) || tuki([i][j][de_donde_vengo][a_donde_voy]) {
            true;
        }
    }

    [...]

    if dp[i][j][de][dondevoy] != null
        

}


i, j donde estamos
a, b de donde venimos
tuki(i, j, a, b)    | pasillo(i, j, a, b)    if m[i][j] == "I"
                    | esquina(i, j, a, b)    if m[i][j] == "L"
                    | cruz(i, j, a, b)    if m[i][j] == "+"
                    | vacio(i, j, a, b)    if m[i][j] == "#"

pasillo(i, j, a, b) | 1 + tuki()    if i == a + 1 && j == b
                    | 1 + tuki()    if i == a && j == b + 1

