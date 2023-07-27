class Power {
    public static void main(String[] args) {
        int base = Integer.parseInt(args[0]);
        int exponent = Integer.parseInt(args[1]);
        int result = 1;

        while (exponent > 0) {
            result = result * base;
            exponent = exponent - 1;
        }

        System.out.println(result);
    }
}
