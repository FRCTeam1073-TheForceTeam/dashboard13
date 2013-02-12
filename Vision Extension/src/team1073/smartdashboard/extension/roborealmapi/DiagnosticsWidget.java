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
import java.io.PrintWriter;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.SimpleDateFormat;
import java.util.AbstractMap;
import java.util.AbstractMap.SimpleEntry;
import java.util.ArrayList;
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
    PrintWriter writer;
    static DiagnosticsWidget instance;
    JLabel label1;
    ArrayList<AbstractMap.SimpleEntry<String, Object>> values;
    int numberOfValues;
    boolean isFirstRow = true;
    String lastKey = "";
    
    @Override
    public void init() {
        instance = this;
        values = new ArrayList<AbstractMap.SimpleEntry<String, Object>>();
        System.out.println("HIIIII MaTT");
        label1 = new JLabel("SCHANAD");
        diagnosticsTable = NetworkTable.getTable("diagnosticsTable");
        Calendar cal = Calendar.getInstance();
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy_MM_dd_HH_mm_ss");
        String path = "C:/WindRiver/workspace/telemetryData/" + sdf.format(cal.getTime())+ ".csv";
        try {          
            writer = new PrintWriter(new BufferedWriter(new FileWriter(path)), true);
        } catch (IOException ex) {
            System.out.println(ex);
        }
        
        diagnosticsTable.addTableListener(new ITableListener()
        {

            @Override
            public void valueChanged(ITable itable, String string, Object o, boolean bln) {
                instance.writeValueToFile(string, o);
                //System.out.println(string + ":  " + o.toString());
            }
        });
        
        add(label1);
    }

    @Override
    public void propertyChanged(Property prprt) {
        
    }
    
    
    private void writeValueToFile(String valueName, Object value)
    {
        if (valueName.equals(lastKey)){
            return;
        }
        
        lastKey = valueName;//seem to be getting 2 changed calls for each value sent
        String rowToWrite = "";
        
        if (values.isEmpty())
        {
            values.add(new SimpleEntry<String, Object> (valueName, value));
        }
        else if (values.get(0).getKey().equals(valueName))
        {
            if (isFirstRow)
            {
                for (int i = 0; i < values.size(); i++)
                {
                    rowToWrite = rowToWrite.concat(values.get(i).getKey() + ",");
                }
                
                rowToWrite = rowToWrite.concat("\n");
                isFirstRow = false;

            }
            
            for (int i = 0; i < values.size(); i++)
            {
                rowToWrite = rowToWrite.concat(values.get(i).getValue().toString() + ",");
            }
            
            
            System.out.println(rowToWrite);
            try
            {
                writer.println(rowToWrite);
            }
            catch (Exception ex)
            {
                System.out.println(ex);
            }
            
            values.clear();
            values.add(0, new SimpleEntry<String, Object> (valueName, value));
        }
        else
        {
            values.add(new SimpleEntry<String, Object> (valueName, value));
        }
       
    }
}
