/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.diagnosticsextension;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.wpilibj.networktables.NetworkTable;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

/**
 *
 * @author Greg
 */
public class DiagnosticsWidget extends StaticWidget{
    TableThread task;
    Values[] newestValues;

    @Override
    public void init() {
        
        newestValues = new Values[64];
        NetworkTable.getTable("diagnostics");
        task = new TableThread();
        
        task.addPropertyChangeListener(new PropertyChangeListener()
            {
                @Override
                public void propertyChange(PropertyChangeEvent evt){
                    if ("progress".equals(evt.getPropertyName())){
                        
                        try
                        {
                            newestValues = task.getSavedValues();
                        }
                        catch (Exception e)
                        {
                            System.out.println("Exception: " + e.toString());
                        }
                    }
                    else
                    {
                        System.out.println("We made it to the else!  " + evt.getPropertyName());
                    }
                }
                
            }
        );
        
        task.execute();
    }

    @Override
    public void propertyChanged(Property prprt) {
        
    }
    
}
