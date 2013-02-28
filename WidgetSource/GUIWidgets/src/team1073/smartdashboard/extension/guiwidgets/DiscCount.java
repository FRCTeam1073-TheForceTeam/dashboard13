package team1073.smartdashboard.extension.guiwidgets;

//import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.gui.Widget;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.smartdashboard.properties.IntegerProperty;
import edu.wpi.first.smartdashboard.types.DataType;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Canvas;
import javax.swing.JFrame;
import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.properties.StringProperty;

public class DiscCount extends Widget{
    
    private int count;
    //private boolean isBottomFlipped;
    //private String combinedData;
    
    //takes a string in format [discNum]#[isBottomFlipped], ex. 0#0 for no discs, bottom not flipped
    public final IntegerProperty newVal = new IntegerProperty(this, "Disc Count", 0);
    public static final DataType[] TYPES = {DataType.NUMBER};
    
    public DiscCount () { 
        count = 0;
        //isBottomFlipped = false;
        //combinedData = count + "," + (isBottomFlipped ? 1 : 0);
    }
    
    @Override
    protected void paintComponent (Graphics graphics) {
        //String[] strings = combinedData.split(",");
        //count = Integer.parseInt(strings[0]);
        //isBottomFlipped = Integer.parseInt(strings[1]) == 1 ? true : false;
        
        graphics.setColor (Color.BLACK);
        graphics.fillRect(60,80,330,100);

        for (int i = 0; i < count; i++) 
        {
            if(count == 4) 
                graphics.setColor(Color.RED);
            else
                graphics.setColor(Color.WHITE);
            graphics.fillOval(i*80+70, 95, 70, 70);
            /*if(isBottomFlipped) {
                graphics.setColor(Color.GRAY);
                graphics.fillOval(75, 100, 60, 60);
            }*/
        }
        graphics.setColor(Color.BLACK);
    }
    
    public void setValue(Object o) {
        int c = count;
        try{c = (Integer)o;}
        catch(Exception e){}
        
        count = c;

        repaint();
    }
    
    @Override
    public void init() {
        count = 0;
        setPreferredSize(new Dimension(400, 200));
    }
    @Override
    public void propertyChanged(Property prprt) {
        setValue(prprt.getValue());
    }  
}