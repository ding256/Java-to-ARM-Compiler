class FizzBuzz {
    public static void main(String [ ] args) {
        System.out.println(args[0]);
        int a = 6;
        while(a > -1) {
            if(a >= 2) {
                System.out.println("Fizz");
            } else {
                System.out.println("Buzz");
            }
            a = a - 1;
        }
    }
}