class Base {
    public static String get_string() {
        return " cs352";
    }

    public static void main(String [ ] args) {
        System.out.print(args[0]);
        String str = get_string();
        System.out.println(str);
    }
}
