class RegisterLoadTest {
    public static void main(String[] args) {
        int n1 = Integer.parseInt(args[0]);
        int n2 = Integer.parseInt(args[1]);
        int n = Integer.parseInt(args[2]);
        int w = 0;
        
        while (n > 0) {
            int x1 = n1 + n2;
            int x2 = n1 - n2;
            int x3 = n1 * n2;
            int x4 = n2 - n1;
            w = w + (x1 * x2) + (x3 * x4);
            n = n - 1;
        }

        System.out.println(w);
    }
}