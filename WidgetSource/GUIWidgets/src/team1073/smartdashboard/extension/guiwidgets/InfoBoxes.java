/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.guiwidgets;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.gui.Widget;
import edu.wpi.first.smartdashboard.properties.Property;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
/**
 *
 * @author Devin
 */
public class InfoBoxes extends Widget{
    
    public void setValue(Object value){
        repaint();
    }
    
    @Override
    public void init() {
        setPreferredSize(new Dimension(600,600));
    }

    @Override
    public void propertyChanged(Property prprt) {
        setValue(prprt.getValue());
    }
    
    @Override
    protected void paintComponent(Graphics graphics){
        Graphics2D g = (Graphics2D) graphics;
        Dimension size  = getSize(); 
        
        g.setColor(Color.BLACK);
        g.setStroke(new BasicStroke (2.0f));
        g.drawRect(50, 50, 380, 390);
        
        g.drawLine(239, 50, 239, 440);
        /*g.drawLine(50, 460, 400, 460);
        
        Font font = new Font("Arial", Font.BOLD, 16);
        graphics.setFont(font);
        g.drawString("Current", 105, 485);
        g.drawString("Calculated", 265, 485);*/
    }
}
