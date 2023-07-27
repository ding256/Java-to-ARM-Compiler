class PellSequence {
    public static int printPellSequence(int n, int a, int b, int count) {
        if (count < n-1) {
            return printPellSequence(n, b, 2 * b + a, count + 1);
        }
        else {
            return a;
        }
    }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        System.out.println(printPellSequence(n, 0, 1, 0));
    }
}
