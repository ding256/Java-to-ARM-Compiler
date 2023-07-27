class RegisterLoadTest {
    public static void main(String[] args) {
        int n1 = Integer.parseInt(args[0]);
        int n2 = Integer.parseInt(args[1]);
        
        int w = (((n1 + n2) * (n1 - n2)) + ((n1 * n2) * (n2 - n1))) + ((((n1 + 2) * (n2 + 2)) - ((n1 + 3) * (n2 + 3))));

        System.out.println(w);
    }
}