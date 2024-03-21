package test;//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Copyright (c) 2023 by Lennard Boetcher (LBmaster)                           +
// Last Modified: 06.03.2023 14:39:32                                          +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Main {

    public static void main(String[] args) throws IOException {
        Path scriptsFolder = Paths.get("C:\\Users\\RalfG\\Desktop\\Projects\\DayZLife\\DayZLifeClient\\scripts");
        Path githubFolder = Paths.get("C:\\Users\\RalfG\\Desktop\\Projects\\");
        process(scriptsFolder, githubFolder, "DayZLifeClient");

        scriptsFolder = Paths.get("C:\\Users\\RalfG\\Desktop\\Projects\\DayZLife\\DayZLifeServer\\scripts");
        githubFolder = Paths.get("C:\\Users\\RalfG\\Desktop\\Projects\\");
        process(scriptsFolder, githubFolder, "DayZLifeServer");
    }

    private static void process(Path scriptsFolder, Path githubFolder, String suffix) throws IOException {
        String[] subFolders = {"1_Core", "2_Gamelib", "3_Game", "4_World", "5_Mission"};
        Map<String, String> moduleFunctions = new HashMap<>();
        for (String module : subFolders) {
            Path folder = scriptsFolder.resolve(module);
            if (!Files.exists(folder))
                continue;
            List<Path> filesInFolder = Files.walk(folder).filter(Files::isRegularFile).toList();
            System.out.println(filesInFolder);
            StringBuilder moduleFunctionsSb = new StringBuilder();
            for (Path file : filesInFolder) {
                String content = processFile(file);
                moduleFunctionsSb.append(content);
            }
            moduleFunctions.put(module, moduleFunctionsSb.toString());
        }
        for (Path templateFolder : findTemplateFolders(githubFolder)) {
            for (Map.Entry<String, String> entry : moduleFunctions.entrySet()) {
                System.out.println("Writing to: " + templateFolder.resolve(entry.getKey() + "_" + suffix + ".c"));
                Files.writeString(templateFolder.resolve(entry.getKey() + "_" + suffix + ".c"), entry.getValue());
            }
        }
    }

    private static List<Path> findTemplateFolders(Path parentFolder) throws IOException {
        return Files.walk(parentFolder).filter(x -> x.getFileName().toString().equalsIgnoreCase("Templates")).toList();
    }

    private static String processFile(Path file) throws IOException {
        String content = Files.readString(file);
        StringBuilder sb = new StringBuilder();
        String[] lines = content.split("\n");
        boolean inClass = false;
        for (String line : lines) {
            String trimmed = line.trim();
            int tabs = 0;
            String tabsString = "";
            while (line.startsWith("\t") || line.startsWith("    ")) {
                tabs++;
                tabsString += "\t";
                if (line.startsWith("\t"))
                    line = line.substring(1);
                else
                    line = line.substring(4);
            }
            if (tabs > (inClass ? 1 : 0) || trimmed.length() == 0)
                continue;
            if (trimmed.equals("{") && sb.toString().trim().endsWith(")")) {
                sb.setLength(sb.length() - 2);
                sb.append(" {\r\n");
            } else if (trimmed.equals("}") && sb.length() > 3 && sb.charAt(sb.length() - 3) == '{') {
                sb.setLength(sb.length() - 2);
                sb.append("}\r\n");
            } else {
                sb.append(tabsString).append(trimmed).append("\r\n");
            }
            if (trimmed.startsWith("class") || trimmed.startsWith("modded") || trimmed.startsWith("enum"))
                inClass = true;
            else if (tabs == 0 && trimmed.startsWith("}"))
                inClass = false;
        }
        return sb.toString();
    }
}
