/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.guiwidgets;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.gui.Widget;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.smartdashboard.properties.DoubleProperty;
import edu.wpi.first.smartdashboard.properties.StringProperty;
import edu.wpi.first.smartdashboard.types.DataType;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;

/**
 *
 * @author Kate
 */
public class speedDisplayCurrent extends StaticWidget {
public static final DataType[] TYPES = { DataType.STRING};
public final StringProperty newVal = new StringProperty(this, "Calc Val", "0,0");

private String combinedData;
private double actualValue = 0.0;
private int calcBoxSize = 16;
private double calcValue = 0.0;

public speedDisplayCurrent () {
    actualValue = 0.0;
    calcValue = 0.0;
    combinedData = actualValue + "," + (calcValue);
}

       public void setValue(Object value){
           
        String s = combinedData;
        try{s = (String) value;}
        catch(Exception e){
            System.out.println("speedDisplayCurrent setValue exception " + e);
        }
        
        combinedData = s;

        repaint();
    }

    @Override
    public void init() {
        setPreferredSize(new Dimension(170, 320));
    }
    
    @Override
    public void propertyChanged(Property prprt) {
        setValue(prprt.getValue());
    }
    
    @Override
    protected void paintComponent(Graphics graphics){
        String[] strings = combinedData.split(",");
        actualValue = Float.parseFloat(strings[0]);
        calcValue = Float.parseFloat(strings[1]);
        
    Graphics2D g = (Graphics2D) graphics;
    Dimension size  = getSize(); 
    
    int height = 200;
    
    Color calcColor = Color.RED;
    
    boolean isCalcGood = false;
    
    int barHeight = (int)(height * actualValue/100.0);
    int calcHeight = (int)(height * calcValue/100.0);
    if (calcHeight <= 200 && calcHeight >= -100) {
        isCalcGood = true;
        calcColor = Color.BLACK;
    }
    
        if (barHeight <= 200 && barHeight >= -100) { //sets limit to 100 
            g.setColor(Color.YELLOW);
            g.fillRect(50, 250 - barHeight, 64, barHeight);
            
            if (isCalcGood) {
            g.setColor(Color.GREEN);
            g.fillRect(50, 250 - (calcHeight + calcBoxSize/2), 64, calcBoxSize);      
            
            g.setColor(Color.BLACK);
            g.setStroke(new BasicStroke (0.5f));
            g.drawLine(50, 250 - (calcHeight + calcBoxSize/2), 113, 250 - (calcHeight + calcBoxSize/2));
            g.drawLine(50, 250 - (calcHeight - calcBoxSize/2), 113, 250 - (calcHeight - calcBoxSize/2));
            
            }
            
            g.setColor(calcColor);
            g.setStroke(new BasicStroke (2.0f));
            g.drawLine(50, 250 - barHeight, 113, 250 - barHeight);
            g.drawRect(50, 50, 64 - 1, 200 - 1);

            g.setColor(Color.BLACK);
            Font font = new Font("Arial", Font.BOLD, 16);
            graphics.setFont(font);
            g.drawString("Curr Speed: " + Integer.toString(Math.abs((int)actualValue)), 35, 272);
            
            g.setColor(calcColor);
            g.drawString("Calc Speed: " + Integer.toString(Math.abs((int)calcValue)), 35, 292);
    }
   
        else { 
            g.setColor(Color.RED);
            g.fillRect(50, 50, 64, 200);
            
            Font font = new Font("Arial", Font.BOLD, 16);
            graphics.setFont(font);
            g.drawString("INVALID SPEED", 27, 272);
        }
    }
}