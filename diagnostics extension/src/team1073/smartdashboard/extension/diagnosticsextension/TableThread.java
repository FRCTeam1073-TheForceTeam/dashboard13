/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.diagnosticsextension;

import edu.wpi.first.wpilibj.networktables.NetworkTable;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Calendar;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.SwingWorker;

/**
 *
 * @author Greg
 */
public class TableThread extends SwingWorker<Values, Values>{

    Values[] values = new Values[64];
    NetworkTable diagnosticsTable;
    Path path;
    Charset encoding = StandardCharsets.UTF_8;
    BufferedWriter writer; 
    
    public Values[] getSavedValues()
    {
        return values;
    }
    
    TableThread()
    {
        diagnosticsTable = NetworkTable.getTable("diagnostics");
        path = Paths.get("C:/WindRiver/workspace/telemetryData/telemetry" + Calendar.DAY_OF_YEAR + "_" + Calendar.HOUR_OF_DAY + "_" + Calendar.MINUTE + "_" + Calendar.SECOND);
        try {
            writer = Files.newBufferedWriter(path, encoding);
        } catch (IOException ex) {
            System.out.println(ex);
        }
    }

    @Override
    protected Values doInBackground() throws Exception {
        
        int numberOfIterations = 0;

        
        while(! isCancelled())
        {
            Thread.sleep(100);
            numberOfIterations++;
            
            //add in more of these calls with real variable names
            this.handleValue("firstValue", 0, true);
            this.handleValue("secondValue", 1, false);
            //
            
            
            setProgress(numberOfIterations % 99);
        }
        
        return null;
        
    }
    
    
    private void handleValue(String valueName, int arrayPos, Boolean isDisplayable)
    {
        values[arrayPos].value = diagnosticsTable.getNumber(valueName);
        values[arrayPos].valueName = valueName;
        values[arrayPos].isDisplayable = isDisplayable;
        this.writeValueToFile(arrayPos);
        
    }
    
    private void writeValueToFile(int arrayPos)
    {
        try
        {
            writer.write(values[arrayPos].valueName + ":   " + values[arrayPos].valueToString());
            writer.newLine();
        }
        catch (Exception ex)
        {
            System.out.println(ex);
        }
        
    }
    
}
