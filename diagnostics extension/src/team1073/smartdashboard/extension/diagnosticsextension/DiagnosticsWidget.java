/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.diagnosticsextension;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.wpilibj.networktables.NetworkTable;
import edu.wpi.first.wpilibj.tables.ITable;
import edu.wpi.first.wpilibj.tables.ITableListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
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
    BufferedWriter writer; 
    static DiagnosticsWidget instance;
    JLabel label1;

    DiagnosticsWidget()
    {
        instance = this;
        System.out.println("LALLALAALAL");
    }
    
    @Override
    public void init() {
        
        System.out.println("HIIIII");
        label1 = new JLabel("SCHANAD");
        diagnosticsTable = NetworkTable.getTable("diagnostics");
        path = Paths.get("C:/WindRiver/workspace/telemetryData/telemetry" + Calendar.DAY_OF_YEAR + "_" + Calendar.HOUR_OF_DAY + "_" + Calendar.MINUTE + "_" + Calendar.SECOND);
        try {
            writer = Files.newBufferedWriter(path, encoding);
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
            writer.write(valueName + ":   " + value.toString());
            writer.newLine();
        }
        catch (Exception ex)
        {
            System.out.println(ex);
        }
        
    }
}
