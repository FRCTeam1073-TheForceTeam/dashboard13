/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.diagnosticsextension;

/**
 *
 * @author Greg
 */
public class Values {
    public String valueName;
    public double value;
    public Boolean isDisplayable;
    
    public String valueToString()
    {
        return Double.toString(value);
    }
}
