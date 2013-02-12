/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.speedometer;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.properties.IntegerProperty;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.smartdashboard.types.DataType;
import java.awt.Dimension;
import java.awt.Graphics;

/**
 *
 * @author Kate
 */
public class Speedometer extends StaticWidget{
    private int speed;
    public final IntegerProperty newVal = new IntegerProperty(this, "Speed", 0);
    public static final DataType[] TYPES = {DataType.NUMBER};
    
    public void init() {
        speed = 0;
        setPreferredSize(new Dimension(200,150));
    }
    
    @Override
    protected void paintComponent(Graphics g) {
        //draw stuff here and mathy logic and stuff
    }
    
    public void setValue(Object o) {
        int d = speed;
       
       try{d = ((Number)o).intValue();;}
       catch(Exception e){}
       
       speed = d;
       
       repaint();
    }
    
    @Override
    public void propertyChanged(Property prprt) {
        setValue(prprt.getValue());
    }  
}
