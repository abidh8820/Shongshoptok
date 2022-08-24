const int maxn = 1e7;
vector <int> primes;
int spf[maxn+5], phi[maxn+5], NOD[maxn+5], cnt[maxn+5], POW[maxn+5]; 
bool prime[maxn+5];
int SOD[maxn+5];
void init(){
    fill(prime+2, prime+maxn+1, 1);
    SOD[1] = NOD[1] = phi[1] = spf[1] = 1;
    for(LL i=2;i<=maxn;i++){
        if(prime[i]) {
            primes.push_back(i), spf[i] = i;
            phi[i] = i-1;
            NOD[i] = 2, cnt[i] = 1;
            SOD[i] = i+1, POW[i] = i;
        }
        for(auto p:primes){
            if(p*i>maxn or p > spf[i]) break;
            prime[p*i] = false, spf[p*i] = p;
            if(i%p == 0){
                phi[p*i]=p*phi[i];
                NOD[p*i]=NOD[i]/(cnt[i]+1)*(cnt[i]+2), cnt[p*i]=cnt[i]+1;
                SOD[p*i]=SOD[i]/SOD[POW[i]]*(SOD[POW[i]]+p*POW[i]),POW[p*i]=p*POW[i];
                break;
            } else {
                phi[p*i]=phi[p]*phi[i];
                NOD[p*i]=NOD[p]*NOD[i], cnt[p*i]=1;
                SOD[p*i]=SOD[p]*SOD[i], POW[p*i]=p;
            }

        }
    }
}

