package party.iroiro.luajava;

import party.iroiro.luajava.pluto.Pluto;

public class PlutoTests {
    @org.junit.jupiter.api.Test
    public void pluto() throws NoSuchMethodException {
        String script = "local a = 2\n" +
                "\n" +
                "switch a do \n" +
                "    case 1:\n" +
                "        print(\"1\")\n" +
                "        break\n" +
                "    case 2:\n" +
                "        print(\"2\")\n" +
                "        break\n" +
                "        \n" +
                "        end\n";
        try(Lua L = new Pluto()){
            L.openLibraries();
            L.run("System = java.import('java.lang.System')");
            L.run("System.out:println('Hello World from Lua!')");
            L.run(script);
        }
    }

}
