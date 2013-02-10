/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.roborealmapi;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.wpilibj.networktables.NetworkTable;
import edu.wpi.first.wpilibj.tables.ITable;
import edu.wpi.first.wpilibj.tables.ITableListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import javax.swing.JLabel;

/**
 *
 * @author Greg
 */
public class DiagnosticsWidget extends StaticWidget{
    NetworkTable diagnosticsTable;
    Path path;
    Charset encoding = StandardCharsets.UTF_8;
    FileWriter writer; 
    static DiagnosticsWidget instance;
    JLabel label1;

    @Override
    public void init() {
        instance = this;
        
        System.out.println("HIIIII MaTT");
        label1 = new JLabel("SCHANAD");
        diagnosticsTable = NetworkTable.getTable("diagnosticsTable");
        Calendar cal = Calendar.getInstance();
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy_MM_dd_HH_mm_ss");
        String path = "C:/WindRiver/workspace/telemetryData/" + sdf.format(cal.getTime())+ ".csv";
        try {          
            writer = new FileWriter(path);
        } catch (IOException ex) {
            System.out.println(ex);
        }
        
        diagnosticsTable.addTableListener(new ITableListener()
        {

            @Override
            public void valueChanged(ITable itable, String string, Object o, boolean bln) {
                instance.writeValueToFile(string, o);
                System.out.println(string + ":  " + o.toString());
            }
        });
        
        add(label1);
    }

    @Override
    public void propertyChanged(Property prprt) {
        
    }
    
    
    private void writeValueToFile(String valueName, Object value)
    {
        try
        {
            writer.append(valueName + "," + value.toString() + "\n");
        }
        catch (Exception ex)
        {
            System.out.println(ex);
        }
        
    }
}
