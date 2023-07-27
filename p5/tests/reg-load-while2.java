class RegisterLoadTest {
    public static void main(String[] args) {
        int n1 = Integer.parseInt(args[0]);
        int n2 = Integer.parseInt(args[1]);
        int n = Integer.parseInt(args[2]);
        int w = 0;
        
        while (n > 0) {
            w = w + ((n1 + n2) * (n1 - n2)) + ((n1 * n2) * (n2 - n1));
            n = n - 1;
        }

        System.out.println(w);
    }
}