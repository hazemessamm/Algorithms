public class EncryptionDriver {

    private int n;
    private int phi;
    private int e;
    private int message_len;
    private int d;
    private boolean e_criteria;

    EncryptionDriver(int message_len, int p, int q, int e) throws ClassNotFoundException {
        this.message_len = message_len;
        this.e = e;
        this.n = p*q;
        this.phi = (p-1)*(q-1);
        //Criteria
        this.e_criteria = (this.e > 1 && e < this.phi) && Class.forName("java.lang.Integer").isInstance(this.e) && this.n % this.e == 0;
    }

    public int gcd(int a, int b)
    {
        if(b == 0)
        {
            return a;
        }
        else
        {
            return gcd(b, a%b);
        }
    }
    //This method for the user to check if gcd(phi(n), e) == 1
    public boolean check_gcd()
    {
        return gcd(this.phi, this.e) == 1;
    }
    public boolean check_e_criteria()
    {
        return e_criteria;
    }
    private void d_generator()
    {
        int k = 0;
        while(true)
        {
            //I found this rule on the internet which is d = (K * phi(n) + 1) / e for some integer K
            this.d = k * this.phi + 1;
            if (this.d % this.e == 0)
            {
                this.d = this.d / e;
                break;
            }
            ++k;
        }
    }
    public double encrypt()
    {
        return Math.pow(message_len, this.e) % this.n;
    }
    public double decrypt()
    {
        d_generator();
        return Math.pow(encrypt(), this.d) % this.n;
    }
    public boolean check_correctness_of_decryption()
    {
        return decrypt() == this.message_len;
    }



}
