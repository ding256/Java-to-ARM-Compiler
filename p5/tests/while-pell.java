class PellSequence {
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        int a = 0;
        int b = 1;
        int count = 0;

        while (count < n-1) {
            int temp = 2 * b + a;
            a = b;
            b = temp;
            count = count + 1;
        }
        System.out.println(a);
    }
}
