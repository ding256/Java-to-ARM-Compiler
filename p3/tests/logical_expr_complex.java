class Base {
    public static void main(String [ ] args) {
        if(!(false || (false && true) || (true && !true))) {
            System.out.println(args[0]);
        } else {
            System.out.println(args[1]);
        }
    }
}