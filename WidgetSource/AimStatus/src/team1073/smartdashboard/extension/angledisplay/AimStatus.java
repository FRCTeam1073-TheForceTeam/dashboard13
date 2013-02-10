package team1073.smartdashboard.extension.angledisplay;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.gui.Widget;
import edu.wpi.first.smartdashboard.properties.BooleanProperty;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.smartdashboard.types.DataType;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;

/**
 *
 * @author Kate
 */
public class AimStatus extends Widget{
    private boolean isLockedOn;
    public final BooleanProperty newVal = new BooleanProperty(this, "Is Locked On", false);
    public static final DataType[] TYPES = {DataType.BOOLEAN};
    
    public AimStatus() {isLockedOn = false;}
    
    @Override
    public void init(){
        isLockedOn = false;
        setPreferredSize(new Dimension(200,50));
    }

    public void setValue(Object o) {
       boolean b = isLockedOn;
       
       try{b = (Boolean) o;}
       catch(Exception e){}
       
       isLockedOn = b;
       repaint();
    }
    
    @Override
    public void propertyChanged(Property prprt) {
        setValue(prprt.getValue());
    }  
    
    @Override
    protected void paintComponent (Graphics graphics) {  
        if(!isLockedOn) {
            graphics.setColor(Color.BLACK);
            graphics.fillRect(10, 10, 200, 50);
        }
        else {
            graphics.setColor(Color.GREEN);
            graphics.fillRect(10, 10, 200, 50);
            graphics.setColor(Color.BLACK);
            graphics.drawString("LOCKED ON", 75, 40);
        }
    }
}