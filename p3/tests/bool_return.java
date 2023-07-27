class Base {
    public static boolean get_bool() {
        return false;
    }

    public static void main(String [ ] args) {
        System.out.println(args[0]);
        if(get_bool()) {
            System.out.println("not printed");
        } else {
            System.out.println("egrl");
        }
    }
}