<?php if ($info["empty"] == false): ?>

<table>
    
      
        <thead>
            <tr> 
                <td>--------Symbol--------</td>
                <td>--------Shares--------</td>
                <td>--------Price---------</td>
                <td>--------Name----------</td>
            </tr>
        </thead>

       
    <?php foreach ($positions as $position): ?>
    
        <tr>
            <td><?= strtoupper($position["symbol"]) ?></td>
            <td><?= $position["shares"] ?></td>
            <td><?= number_format($position["price"] , 2) ?></td>
            <td><?= $position["name"] ?></td>
        </tr>
    
    <?php endforeach ?>
</table>

<?php else: ?>

<h2> You ain't got no stock! </h2>



<?php endif ?>
    

<h2> Available Cash: <?=number_format($info["cash"] , 2)?>$ </h2>
