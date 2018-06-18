<?php

include('../../application/login/model/LoginModel.php');

class LoginTest extends PHPUnit_Framework_TestCase
{
	private $DB;
	
	public function __construct()
	{
		$this->DB = new PDO('mysql:dbname=AbOut_Test;host=localhost', 'web_user', 'resu_bew');
		
		$this->model = new LoginModel($this->DB, $this->DB);
	}

    public function test_getUser()
    {
		$result = $this->model->getUser('bjbutcher');
		$this->assertEquals(4, $result['userId']);
		$this->assertEquals('Ben Butcher/Michele', $result['uName']);
		$this->assertEquals(1, $result['activeFlag']);
		
		$result = $this->model->getUser('fakeUser');
		$this->assertEmpty($result);
    }
	
	public function test_getDefaultSemester()
	{
		$result = $this->model->getDefaultSemester();
		$this->assertEquals(10, $result);		
	}
	
	public function test_getSemester()
	{
		$result = $this->model->getSemester(8);
		$this->assertEquals('Summer 2013', $result);
		
		$result = $this->model->getSemester(5);
		$this->assertEmpty($result);
	}
}
?>
