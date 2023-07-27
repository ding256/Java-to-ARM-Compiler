class SumOfSquares {
    public static int sumOfSquares(int n) {
        if (n == 0) return 0;
        else return n * n + sumOfSquares(n - 1);
    }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        System.out.println(sumOfSquares(n));
    }
}
